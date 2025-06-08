#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Análise Comparativa de Comentários: IA vs Humanos
Script para comparar comentários gerados pelo DeepSeek com comentários originais
"""

import os
import re
import json
import csv
from collections import defaultdict
from dataclasses import dataclass, asdict
from typing import List, Dict, Tuple
import statistics
from datetime import datetime

# Métricas avançadas
import nltk
from nltk.translate.bleu_score import sentence_bleu, SmoothingFunction
from nltk.translate.meteor_score import meteor_score
from rouge_score import rouge_scorer
from difflib import SequenceMatcher
import textstat

# Download necessário do NLTK
try:
    nltk.data.find('tokenizers/punkt')
except LookupError:
    nltk.download('punkt')
try:
    nltk.data.find('corpora/wordnet')
except LookupError:
    nltk.download('wordnet')

@dataclass
class CommentPair:
    """Representa um par de comentários (humano vs IA)"""
    file_path: str
    line_number: int
    human_comment: str
    ai_comment: str
    language: str
    
@dataclass
class MetricScores:
    """Representa as pontuações de todas as métricas para um comentário"""
    similarity_score: float  # Métrica 1: Similaridade semântica
    length_ratio: float      # Métrica 2: Proporção de tamanho
    readability_score: float # Métrica 3: Legibilidade 
    bleu_score: float       # Métrica 4: BLEU score
    rouge_score: float      # Métrica 5: ROUGE score
    overall_score: float    # Score geral

class CommentAnalyzer:
    """Classe principal para análise de comentários"""
    
    def __init__(self):
        self.comment_pairs: List[CommentPair] = []
        self.scores: List[MetricScores] = []
        self.smoothie = SmoothingFunction().method4
        self.rouge_scorer = rouge_scorer.RougeScorer(['rouge1', 'rougeL'], use_stemmer=True)
        
        # Diretórios
        self.original_dir = "grpc-original"
        self.ai_dirs = {
            'cc': 'grpc-result-comments-cc',
            'python': 'grpc-result-comments-python', 
            'ruby': 'grpc-result-comments-ruby'
        }
        
    def is_copyright_comment(self, comment: str) -> bool:
        """Verifica se é um comentário de copyright para ignorar"""
        copyright_patterns = [
            r'copyright', r'license', r'author', r'@license',
            r'all rights reserved', r'permission', r'redistribution',
            r'apache', r'gpl', r'mit', r'bsd'
        ]
        comment_lower = comment.lower()
        return any(re.search(pattern, comment_lower) for pattern in copyright_patterns)
    
    def extract_comments_by_language(self, file_path: str, language: str) -> List[Tuple[str, int]]:
        """Extrai comentários baseado na linguagem"""
        try:
            with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except:
            return []
            
        comments = []
        
        if language in ['cc', 'cpp']:
            # C++ comments
            line_comments = re.finditer(r'//(.*)$', content, re.MULTILINE)
            block_comments = re.finditer(r'/\*(.*?)\*/', content, re.DOTALL)
            
            for match in line_comments:
                line_num = content[:match.start()].count('\n') + 1
                comment_text = match.group(1).strip()
                if comment_text and not self.is_copyright_comment(comment_text):
                    comments.append((comment_text, line_num))
                    
            for match in block_comments:
                line_num = content[:match.start()].count('\n') + 1
                comment_text = match.group(1).strip()
                if comment_text and not self.is_copyright_comment(comment_text):
                    comments.append((comment_text, line_num))
                    
        elif language == 'python':
            # Python comments
            line_comments = re.finditer(r'#(.*)$', content, re.MULTILINE)
            docstrings = re.finditer(r'"""(.*?)"""', content, re.DOTALL)
            
            for match in line_comments:
                line_num = content[:match.start()].count('\n') + 1
                comment_text = match.group(1).strip()
                if comment_text and not self.is_copyright_comment(comment_text):
                    comments.append((comment_text, line_num))
                    
            for match in docstrings:
                line_num = content[:match.start()].count('\n') + 1
                comment_text = match.group(1).strip()
                if comment_text and not self.is_copyright_comment(comment_text):
                    comments.append((comment_text, line_num))
                    
        elif language == 'ruby':
            # Ruby comments
            line_comments = re.finditer(r'#(.*)$', content, re.MULTILINE)
            
            for match in line_comments:
                line_num = content[:match.start()].count('\n') + 1
                comment_text = match.group(1).strip()
                if comment_text and not self.is_copyright_comment(comment_text):
                    comments.append((comment_text, line_num))
        
        return comments
    
    def get_matching_files(self, language: str) -> List[str]:
        """Encontra arquivos correspondentes entre original e IA"""
        original_files = set()
        ai_files = set()
        
        # Extensões por linguagem
        extensions = {
            'cc': ['.cc', '.h', '.cpp', '.hpp'],
            'python': ['.py'],
            'ruby': ['.rb']
        }
        
        # Coleta arquivos originais
        for root, _, files in os.walk(self.original_dir):
            for file in files:
                if any(file.endswith(ext) for ext in extensions[language]):
                    rel_path = os.path.relpath(os.path.join(root, file), self.original_dir)
                    original_files.add(rel_path)
        
        # Coleta arquivos da IA
        ai_dir = self.ai_dirs[language]
        if os.path.exists(ai_dir):
            for root, _, files in os.walk(ai_dir):
                for file in files:
                    if any(file.endswith(ext) for ext in extensions[language]):
                        rel_path = os.path.relpath(os.path.join(root, file), ai_dir)
                        ai_files.add(rel_path)
        
        return list(original_files & ai_files)
    
    def collect_comment_pairs(self):
        """Coleta todos os pares de comentários para análise"""
        print("🔍 Coletando pares de comentários...")
        
        for language in self.ai_dirs.keys():
            print(f"\n📁 Processando arquivos {language.upper()}...")
            matching_files = self.get_matching_files(language)
            print(f"   Encontrados {len(matching_files)} arquivos correspondentes")
            
            for file_path in matching_files:
                original_file = os.path.join(self.original_dir, file_path)
                ai_file = os.path.join(self.ai_dirs[language], file_path)
                
                human_comments = self.extract_comments_by_language(original_file, language)
                ai_comments = self.extract_comments_by_language(ai_file, language)
                
                # Emparelha comentários por posição
                min_len = min(len(human_comments), len(ai_comments))
                for i in range(min_len):
                    human_text, human_line = human_comments[i]
                    ai_text, ai_line = ai_comments[i]
                    
                    self.comment_pairs.append(CommentPair(
                        file_path=file_path,
                        line_number=human_line,
                        human_comment=human_text,
                        ai_comment=ai_text,
                        language=language
                    ))
        
        print(f"\n✅ Total de {len(self.comment_pairs)} pares de comentários coletados")
    
    def calculate_similarity_score(self, human: str, ai: str) -> float:
        """Métrica 1: Calcula similaridade semântica usando SequenceMatcher"""
        return SequenceMatcher(None, human.lower(), ai.lower()).ratio()
    
    def calculate_length_ratio(self, human: str, ai: str) -> float:
        """Métrica 2: Calcula proporção de tamanho (penaliza diferenças extremas)"""
        if len(human) == 0 and len(ai) == 0:
            return 1.0
        if len(human) == 0 or len(ai) == 0:
            return 0.0
        
        ratio = min(len(human), len(ai)) / max(len(human), len(ai))
        return ratio
    
    def calculate_readability_score(self, human: str, ai: str) -> float:
        """Métrica 3: Compara legibilidade usando Flesch Reading Ease"""
        if len(human.strip()) < 10 or len(ai.strip()) < 10:
            return 0.5  # Score neutro para comentários muito curtos
            
        try:
            human_readability = textstat.flesch_reading_ease(human)
            ai_readability = textstat.flesch_reading_ease(ai)
            
            # Normaliza para 0-1, onde valores próximos indicam legibilidade similar
            diff = abs(human_readability - ai_readability)
            normalized_score = max(0, 1 - (diff / 100))
            return normalized_score
        except:
            return 0.5
    
    def calculate_bleu_score(self, human: str, ai: str) -> float:
        """Métrica 4: Calcula BLEU score"""
        human_tokens = human.lower().split()
        ai_tokens = ai.lower().split()
        
        if not human_tokens or not ai_tokens:
            return 0.0
            
        return sentence_bleu([human_tokens], ai_tokens, smoothing_function=self.smoothie)
    
    def calculate_rouge_score(self, human: str, ai: str) -> float:
        """Métrica 5: Calcula ROUGE score (média de ROUGE-1 e ROUGE-L)"""
        if not human.strip() or not ai.strip():
            return 0.0
            
        scores = self.rouge_scorer.score(human, ai)
        rouge1 = scores['rouge1'].fmeasure
        rougeL = scores['rougeL'].fmeasure
        return (rouge1 + rougeL) / 2
    
    def calculate_metrics(self):
        """Calcula todas as métricas para cada par de comentários"""
        print("\n📊 Calculando métricas...")
        
        for pair in self.comment_pairs:
            similarity = self.calculate_similarity_score(pair.human_comment, pair.ai_comment)
            length_ratio = self.calculate_length_ratio(pair.human_comment, pair.ai_comment)
            readability = self.calculate_readability_score(pair.human_comment, pair.ai_comment)
            bleu = self.calculate_bleu_score(pair.human_comment, pair.ai_comment)
            rouge = self.calculate_rouge_score(pair.human_comment, pair.ai_comment)
            
            # Score geral (média ponderada)
            overall = (similarity * 0.25 + length_ratio * 0.15 + 
                      readability * 0.15 + bleu * 0.25 + rouge * 0.20)
            
            metrics = MetricScores(
                similarity_score=similarity,
                length_ratio=length_ratio,
                readability_score=readability,
                bleu_score=bleu,
                rouge_score=rouge,
                overall_score=overall
            )
            
            self.scores.append(metrics)
        
        print("✅ Métricas calculadas com sucesso!")
    
    def generate_statistics(self) -> Dict:
        """Gera estatísticas gerais"""
        if not self.scores:
            return {}
            
        stats = {}
        metrics = ['similarity_score', 'length_ratio', 'readability_score', 
                  'bleu_score', 'rouge_score', 'overall_score']
        
        for metric in metrics:
            values = [getattr(score, metric) for score in self.scores]
            stats[metric] = {
                'média': statistics.mean(values),
                'mediana': statistics.median(values),
                'desvio_padrão': statistics.stdev(values) if len(values) > 1 else 0,
                'mínimo': min(values),
                'máximo': max(values)
            }
        
        return stats
    
    def get_best_and_worst_comments(self) -> Tuple[List, List]:
        """Identifica os 10 melhores e 10 piores comentários"""
        paired_data = list(zip(self.comment_pairs, self.scores))
        
        # Ordena por score geral
        sorted_by_score = sorted(paired_data, key=lambda x: x[1].overall_score, reverse=True)
        
        best_10 = sorted_by_score[:10]
        worst_10 = sorted_by_score[-10:]
        
        return best_10, worst_10
    
    def generate_conclusion(self, stats: Dict) -> str:
        """Gera conclusão do experimento"""
        overall_avg = stats['overall_score']['média']
        
        conclusion = f"""
# CONCLUSÕES DO EXPERIMENTO

## Resumo Executivo
A análise comparativa entre comentários gerados pelo DeepSeek e comentários escritos por desenvolvedores humanos revelou insights importantes sobre a capacidade atual da IA em documentação de código.

## Principais Descobertas

### Score Geral: {overall_avg:.3f}/1.000
- **Interpretação**: {'Excelente' if overall_avg > 0.8 else 'Bom' if overall_avg > 0.6 else 'Moderado' if overall_avg > 0.4 else 'Baixo'}

### Análise por Métrica:

1. **Similaridade Semântica**: {stats['similarity_score']['média']:.3f}
   - Mede o quão similar é o conteúdo dos comentários
   - {'Alta similaridade' if stats['similarity_score']['média'] > 0.7 else 'Similaridade moderada' if stats['similarity_score']['média'] > 0.5 else 'Baixa similaridade'}

2. **Proporção de Tamanho**: {stats['length_ratio']['média']:.3f}
   - Avalia se a IA mantém tamanhos apropriados
   - {'Tamanhos consistentes' if stats['length_ratio']['média'] > 0.7 else 'Variação moderada' if stats['length_ratio']['média'] > 0.5 else 'Grande variação de tamanho'}

3. **Legibilidade**: {stats['readability_score']['média']:.3f}
   - Compara facilidade de leitura
   - {'Legibilidade similar' if stats['readability_score']['média'] > 0.7 else 'Diferenças moderadas' if stats['readability_score']['média'] > 0.5 else 'Grandes diferenças de legibilidade'}

4. **BLEU Score**: {stats['bleu_score']['média']:.3f}
   - Métrica padrão para qualidade de texto
   - {'Qualidade alta' if stats['bleu_score']['média'] > 0.3 else 'Qualidade moderada' if stats['bleu_score']['média'] > 0.1 else 'Qualidade baixa'}

5. **ROUGE Score**: {stats['rouge_score']['média']:.3f}
   - Mede sobreposição de conteúdo
   - {'Alta sobreposição' if stats['rouge_score']['média'] > 0.3 else 'Sobreposição moderada' if stats['rouge_score']['média'] > 0.1 else 'Baixa sobreposição'}

## Recomendações

### Pontos Fortes da IA:
- {"Mantém estrutura similar aos comentários humanos" if stats['similarity_score']['média'] > 0.6 else ""}
- {"Produz comentários de tamanho apropriado" if stats['length_ratio']['média'] > 0.6 else ""}

### Áreas para Melhoria:
- {"Melhorar similaridade semântica" if stats['similarity_score']['média'] < 0.6 else ""}
- {"Ajustar tamanho dos comentários" if stats['length_ratio']['média'] < 0.6 else ""}
- {"Aprimorar legibilidade" if stats['readability_score']['média'] < 0.6 else ""}

## Impacto para Manutenção de Software
{"A IA demonstra capacidade adequada para auxiliar na documentação de código, podendo ser uma ferramenta valiosa para desenvolvedores." if overall_avg > 0.6 else "A IA ainda precisa de aprimoramentos significativos antes de ser considerada uma alternativa viável para documentação automática de código."}

---
*Análise realizada em {datetime.now().strftime('%d/%m/%Y às %H:%M')}*
*Total de comentários analisados: {len(self.comment_pairs)}*
        """
        
        return conclusion.strip()
    
    def export_results(self):
        """Exporta todos os resultados para arquivos"""
        print("\n📁 Exportando resultados...")
        
        # Cria diretório de resultados
        results_dir = "results_analysis"
        os.makedirs(results_dir, exist_ok=True)
        
        # 1. Estatísticas gerais
        stats = self.generate_statistics()
        with open(f"{results_dir}/estatisticas_gerais.json", 'w', encoding='utf-8') as f:
            json.dump(stats, f, indent=2, ensure_ascii=False)
        
        # 2. Dados completos em CSV
        with open(f"{results_dir}/dados_completos.csv", 'w', newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(['Arquivo', 'Linha', 'Linguagem', 'Comentário_Humano', 'Comentário_IA',
                           'Score_Similaridade', 'Razão_Tamanho', 'Score_Legibilidade',
                           'Score_BLEU', 'Score_ROUGE', 'Score_Geral'])
            
            for pair, score in zip(self.comment_pairs, self.scores):
                writer.writerow([
                    pair.file_path, pair.line_number, pair.language,
                    pair.human_comment, pair.ai_comment,
                    f"{score.similarity_score:.4f}", f"{score.length_ratio:.4f}",
                    f"{score.readability_score:.4f}", f"{score.bleu_score:.4f}",
                    f"{score.rouge_score:.4f}", f"{score.overall_score:.4f}"
                ])
        
        # 3. Melhores e piores comentários
        best_10, worst_10 = self.get_best_and_worst_comments()
        
        # Melhores comentários
        with open(f"{results_dir}/top_10_melhores.md", 'w', encoding='utf-8') as f:
            f.write("# TOP 10 MELHORES COMENTÁRIOS\n\n")
            for i, (pair, score) in enumerate(best_10, 1):
                f.write(f"## #{i} - Score: {score.overall_score:.4f}\n")
                f.write(f"**Arquivo**: {pair.file_path} (linha {pair.line_number})\n")
                f.write(f"**Linguagem**: {pair.language}\n\n")
                f.write("**Comentário Humano:**\n")
                f.write(f"```\n{pair.human_comment}\n```\n\n")
                f.write("**Comentário IA:**\n")
                f.write(f"```\n{pair.ai_comment}\n```\n\n")
                f.write("**Métricas:**\n")
                f.write(f"- Similaridade: {score.similarity_score:.3f}\n")
                f.write(f"- Razão Tamanho: {score.length_ratio:.3f}\n")
                f.write(f"- Legibilidade: {score.readability_score:.3f}\n")
                f.write(f"- BLEU: {score.bleu_score:.3f}\n")
                f.write(f"- ROUGE: {score.rouge_score:.3f}\n\n")
                f.write("---\n\n")
        
        # Piores comentários
        with open(f"{results_dir}/top_10_piores.md", 'w', encoding='utf-8') as f:
            f.write("# TOP 10 PIORES COMENTÁRIOS\n\n")
            for i, (pair, score) in enumerate(worst_10, 1):
                f.write(f"## #{i} - Score: {score.overall_score:.4f}\n")
                f.write(f"**Arquivo**: {pair.file_path} (linha {pair.line_number})\n")
                f.write(f"**Linguagem**: {pair.language}\n\n")
                f.write("**Comentário Humano:**\n")
                f.write(f"```\n{pair.human_comment}\n```\n\n")
                f.write("**Comentário IA:**\n")
                f.write(f"```\n{pair.ai_comment}\n```\n\n")
                f.write("**Métricas:**\n")
                f.write(f"- Similaridade: {score.similarity_score:.3f}\n")
                f.write(f"- Razão Tamanho: {score.length_ratio:.3f}\n")
                f.write(f"- Legibilidade: {score.readability_score:.3f}\n")
                f.write(f"- BLEU: {score.bleu_score:.3f}\n")
                f.write(f"- ROUGE: {score.rouge_score:.3f}\n\n")
                f.write("---\n\n")
        
        # 4. Conclusão do experimento
        conclusion = self.generate_conclusion(stats)
        with open(f"{results_dir}/conclusao_experimento.md", 'w', encoding='utf-8') as f:
            f.write(conclusion)
        
        # 5. Resumo executivo para apresentação
        with open(f"{results_dir}/resumo_apresentacao.md", 'w', encoding='utf-8') as f:
            f.write("# RESUMO EXECUTIVO - APRESENTAÇÃO\n\n")
            f.write("## Métricas Principais\n\n")
            f.write(f"| Métrica | Score | Interpretação |\n")
            f.write(f"|---------|--------|---------------|\n")
            for metric, data in stats.items():
                if metric != 'overall_score':
                    name = metric.replace('_', ' ').title()
                    score = data['média']
                    interpretation = 'Alto' if score > 0.7 else 'Médio' if score > 0.4 else 'Baixo'
                    f.write(f"| {name} | {score:.3f} | {interpretation} |\n")
            
            f.write(f"\n**Score Geral: {stats['overall_score']['média']:.3f}/1.000**\n\n")
            
            f.write("## Principais Achados\n\n")
            f.write(f"- Total de comentários analisados: **{len(self.comment_pairs)}**\n")
            f.write(f"- Linguagens avaliadas: **C++, Python, Ruby**\n")
            f.write(f"- Score médio geral: **{stats['overall_score']['média']:.3f}**\n")
            f.write(f"- Melhor score individual: **{stats['overall_score']['máximo']:.3f}**\n")
            f.write(f"- Pior score individual: **{stats['overall_score']['mínimo']:.3f}**\n")
        
        print(f"✅ Resultados exportados para o diretório '{results_dir}'")
        return results_dir

    def run_complete_analysis(self):
        """Executa análise completa"""
        print("🚀 Iniciando análise comparativa completa...")
        print("=" * 60)
        
        # Coleta dados
        self.collect_comment_pairs()
        
        if not self.comment_pairs:
            print("❌ Nenhum par de comentários encontrado!")
            return
        
        # Calcula métricas
        self.calculate_metrics()
        
        # Exporta resultados
        results_dir = self.export_results()
        
        print("\n🎉 Análise concluída com sucesso!")
        print(f"📊 Resultados disponíveis em: {results_dir}/")
        print("\nArquivos gerados:")
        print("├── estatisticas_gerais.json")
        print("├── dados_completos.csv")
        print("├── top_10_melhores.md")
        print("├── top_10_piores.md")
        print("├── conclusao_experimento.md")
        print("└── resumo_apresentacao.md")

if __name__ == "__main__":
    analyzer = CommentAnalyzer()
    analyzer.run_complete_analysis()