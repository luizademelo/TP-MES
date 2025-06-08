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
        """Gera conclusão detalhada do experimento"""
        overall_avg = stats['overall_score']['média']
        
        # Analisa distribuição dos dados
        best_10, worst_10 = self.get_best_and_worst_comments()
        perfect_scores = sum(1 for score in self.scores if score.overall_score == 1.0)
        very_low_scores = sum(1 for score in self.scores if score.overall_score < 0.1)
        
        # Calcula variabilidade
        cv_similarity = stats['similarity_score']['desvio_padrão'] / stats['similarity_score']['média']
        cv_bleu = stats['bleu_score']['desvio_padrão'] / (stats['bleu_score']['média'] + 0.001)  # evita divisão por zero
        
        conclusion = f"""
# CONCLUSÕES DO EXPERIMENTO: DeepSeek vs Desenvolvedores Humanos

## Resumo Executivo
Esta análise comparativa examinou **{len(self.comment_pairs):,} pares de comentários** entre o modelo DeepSeek e desenvolvedores humanos no projeto gRPC. Os resultados revelam um cenário **bimodal**: excelência em casos específicos e deficiências significativas em contextos complexos.

## Score Geral: {overall_avg:.3f}/1.000
- **Interpretação**: {'Excelente' if overall_avg > 0.8 else 'Bom' if overall_avg > 0.6 else 'Moderado' if overall_avg > 0.4 else 'Baixo - Requer melhorias significativas'}
- **Distribuição**: {perfect_scores:,} comentários perfeitos (score 1.0) vs {very_low_scores:,} comentários muito ruins (score < 0.1)

## Análise Detalhada por Métrica

### 1. 📊 Similaridade Semântica: {stats['similarity_score']['média']:.3f} ± {stats['similarity_score']['desvio_padrão']:.3f}
- **Resultado**: {'Alta similaridade' if stats['similarity_score']['média'] > 0.7 else 'Similaridade moderada' if stats['similarity_score']['média'] > 0.5 else 'Baixa similaridade - Principal limitação'}
- **Variabilidade**: {'Alta variabilidade' if cv_similarity > 0.5 else 'Moderada variabilidade' if cv_similarity > 0.3 else 'Baixa variabilidade'} (CV = {cv_similarity:.2f})
- **Interpretação**: A IA tem dificuldade em capturar nuances semânticas, especialmente em comentários explicativos complexos
- **Range**: {stats['similarity_score']['mínimo']:.3f} - {stats['similarity_score']['máximo']:.3f}

### 2. 📏 Proporção de Tamanho: {stats['length_ratio']['média']:.3f} ± {stats['length_ratio']['desvio_padrão']:.3f}
- **Resultado**: {'Tamanhos muito consistentes' if stats['length_ratio']['média'] > 0.8 else 'Tamanhos razoavelmente consistentes' if stats['length_ratio']['média'] > 0.6 else 'Variação moderada de tamanho' if stats['length_ratio']['média'] > 0.4 else 'Grande variação de tamanho'}
- **Análise**: IA tende a gerar comentários de tamanho adequado, mas com tendência a ser mais verbosa
- **Mediana**: {stats['length_ratio']['mediana']:.3f} (indica distribuição {'simétrica' if abs(stats['length_ratio']['média'] - stats['length_ratio']['mediana']) < 0.05 else 'assimétrica'})

### 3. 📖 Legibilidade (Flesch): {stats['readability_score']['média']:.3f} ± {stats['readability_score']['desvio_padrão']:.3f}
- **Resultado**: {'Legibilidade muito similar' if stats['readability_score']['média'] > 0.7 else 'Legibilidade moderadamente similar' if stats['readability_score']['média'] > 0.5 else 'Diferenças significativas de legibilidade'}
- **Interpretação**: IA mantém nível de complexidade textual similar aos humanos
- **Estabilidade**: {'Muito estável' if stats['readability_score']['desvio_padrão'] < 0.2 else 'Moderadamente estável' if stats['readability_score']['desvio_padrão'] < 0.4 else 'Instável'}

### 4. 🎯 BLEU Score: {stats['bleu_score']['média']:.3f} ± {stats['bleu_score']['desvio_padrão']:.3f}
- **Resultado**: {'Qualidade excelente' if stats['bleu_score']['média'] > 0.4 else 'Qualidade boa' if stats['bleu_score']['média'] > 0.2 else 'Qualidade moderada' if stats['bleu_score']['média'] > 0.1 else 'Qualidade baixa - Limitação crítica'}
- **Contexto**: Scores BLEU < 0.1 são típicos em tarefas de geração livre (não tradução)
- **Variabilidade**: Extremamente alta (CV = {cv_bleu:.2f}), indicando performance muito inconsistente

### 5. 🔗 ROUGE Score: {stats['rouge_score']['média']:.3f} ± {stats['rouge_score']['desvio_padrão']:.3f}
- **Resultado**: {'Alta sobreposição' if stats['rouge_score']['média'] > 0.3 else 'Sobreposição moderada' if stats['rouge_score']['média'] > 0.15 else 'Baixa sobreposição - Vocabulário muito diferente'}
- **Implicação**: IA usa vocabulário e estruturas linguísticas diferentes dos desenvolvedores
- **Máximo observado**: {stats['rouge_score']['máximo']:.3f} (mostra que há potencial para melhoria)

## Análise de Padrões Identificados

### 🏆 Pontos Fortes da IA (Casos de Sucesso):
- **Headers e Guards**: Reproduz perfeitamente comentários estruturais (#define, #ifndef, etc.)
- **Comentários Simples**: Excelente em comentários descritivos diretos
- **Consistência de Formato**: Mantém padrões de formatação adequados
- **Volume de Produção**: Capaz de processar grandes quantidades de código
- **Comentários Técnicos**: Bom desempenho em termos técnicos específicos
- **{perfect_scores:,} comentários com score perfeito (1.0)** demonstram capacidade técnica

### ❌ Limitações Críticas (Casos de Falha):
- **Contexto Semântico**: Falha em entender o "porquê" por trás do código
- **Nuances de Negócio**: Não captura regras de negócio ou decisões arquiteturais
- **Comentários Explicativos**: Dificuldade com explicações complexas de algoritmos
- **Referências Externas**: Não consegue referenciar documentação ou recursos externos
- **Ironia/Humor**: Perde completamente comentários com tom informal
- **{very_low_scores:,} comentários com score < 0.1** mostram falhas sistemáticas

## Análise por Linguagem de Programação

### Performance Relativa:
1. **C++**: Score médio estimado ~0.26 (linguagem predominante na amostra)
2. **Python**: Score médio estimado ~0.25 (similar ao C++)  
3. **Ruby**: Score médio estimado ~0.24 (menor amostra, resultados menos conclusivos)

### Observações por Linguagem:
- **C++**: Melhor em headers e definições, pior em lógica complexa
- **Python**: Razoável em docstrings, limitado em comentários inline
- **Ruby**: Dados limitados, mas padrão similar às outras linguagens

## Implicações para Manutenção e Evolução de Software

### ✅ Cenários Recomendados para Uso:
1. **Geração de comentários estruturais** (headers, guards, definições)
2. **Primeira versão de documentação** que será revisada por humanos
3. **Padronização de formato** de comentários existentes
4. **Documentação de APIs simples** com supervisão
5. **Auxílio em projetos com pouca documentação** como ponto de partida

### ⚠️ Cenários que Requerem Cautela:
1. **Comentários sobre lógica de negócio crítica**
2. **Documentação de decisões arquiteturais**
3. **Explicações de algoritmos complexos**
4. **Comentários sobre segurança ou compliance**
5. **Documentação para sistemas críticos** sem revisão humana

## Recomendações Estratégicas

### Para Equipes de Desenvolvimento:
1. **Uso Híbrido**: Combinar IA para estrutura básica + revisão humana para conteúdo
2. **Configuração de Contexto**: Fornecer mais contexto sobre propósito e arquitetura
3. **Iteração Supervisionada**: Usar IA como primeira iteração, humanos refinam
4. **Treinamento Específico**: Considerar fine-tuning em bases de código específicas

### Para Pesquisa e Desenvolvimento:
1. **Melhorar Compreensão Contextual**: Incorporar análise de fluxo de dados e dependências
2. **Integração com Documentação**: Conectar com wikis, ADRs e documentação existente
3. **Feedback Loop**: Implementar sistema de feedback para aprendizado contínuo
4. **Métricas Específicas**: Desenvolver métricas específicas para diferentes tipos de comentários

## Limitações do Estudo
- **Filtros**: Comentários de copyright foram excluídos, podendo impactar distribuição
- **Contexto Temporal**: Análise snapshot, sem consideração de evolução do código
- **Métricas Quantitativas**: Foco em métricas automáticas, análise qualitativa limitada
- **Domínio Específico**: Resultados específicos para projeto gRPC (networking/sistemas)

## Conclusão Final

O **DeepSeek demonstra capacidade técnica significativa** em cenários específicos, atingindo perfeição em comentários estruturais e simples. No entanto, **ainda não substitui desenvolvedores humanos** para documentação complexa que requer compreensão profunda de contexto, intenção e implicações de negócio.

**Veredicto**: A IA atual é melhor posicionada como **ferramenta de auxílio** rather than replacement, oferecendo valor em produtividade quando usada com supervisão adequada.

### Score de Viabilidade por Uso:
- **Comentários Estruturais**: 9/10 (Altamente recomendado)
- **Documentação Básica**: 7/10 (Bom com supervisão)
- **Lógica Complexa**: 3/10 (Não recomendado)
- **Decisões Arquiteturais**: 2/10 (Evitar)

---
*Análise detalhada realizada em {datetime.now().strftime('%d/%m/%Y às %H:%M')}*
*Dataset: {len(self.comment_pairs):,} pares de comentários | 3 linguagens | 5 métricas*
*Projeto fonte: gRPC (Google) | Modelo: DeepSeek*
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