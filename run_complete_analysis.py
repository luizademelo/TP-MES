#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script Principal - Análise Completa de Comentários
Executa toda a pipeline de análise: coleta, métricas, relatórios e visualizações
"""

import sys
import os
import subprocess
import time
from datetime import datetime

def install_requirements():
    """Instala as dependências necessárias"""
    print("📦 Instalando dependências...")
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", "-r", "requirements_analysis.txt"])
        print("✅ Dependências instaladas com sucesso!")
        return True
    except subprocess.CalledProcessError as e:
        print(f"❌ Erro ao instalar dependências: {e}")
        return False

def run_main_analysis():
    """Executa a análise principal de comentários"""
    print("\n🔍 Executando análise principal...")
    try:
        from comprehensive_comment_analysis import CommentAnalyzer
        analyzer = CommentAnalyzer()
        analyzer.run_complete_analysis()
        return True
    except Exception as e:
        print(f"❌ Erro na análise principal: {e}")
        return False

def generate_visualizations():
    """Gera as visualizações dos resultados"""
    print("\n🎨 Gerando visualizações...")
    try:
        from generate_visualizations import VisualizationGenerator
        visualizer = VisualizationGenerator()
        visualizer.generate_all_visualizations()
        return True
    except Exception as e:
        print(f"❌ Erro ao gerar visualizações: {e}")
        return False

def create_presentation_summary():
    """Cria um resumo final para apresentação"""
    print("\n📋 Criando resumo final...")
    
    summary_content = f"""
# ANÁLISE COMPARATIVA: COMENTÁRIOS IA vs HUMANOS

## Data da Análise
{datetime.now().strftime('%d/%m/%Y às %H:%M')}

## Objetivo
Comparar comentários de código gerados pelo DeepSeek com comentários escritos por desenvolvedores humanos no projeto gRPC do Google.

## Metodologia

### 5 Métricas Implementadas:
1. **Similaridade Semântica** - Mede quão similar é o conteúdo dos comentários
2. **Proporção de Tamanho** - Avalia se a IA mantém tamanhos apropriados  
3. **Legibilidade** - Compara facilidade de leitura usando Flesch Reading Ease
4. **BLEU Score** - Métrica padrão para qualidade de texto
5. **ROUGE Score** - Mede sobreposição de conteúdo

### Linguagens Analisadas:
- **C/C++** (.cc, .h, .cpp, .hpp)
- **Python** (.py)
- **Ruby** (.rb)

## Arquivos Gerados

### Dados e Análises:
- `estatisticas_gerais.json` - Estatísticas completas de todas as métricas
- `dados_completos.csv` - Dataset completo para análises adicionais
- `top_10_melhores.md` - Os 10 comentários com melhor score
- `top_10_piores.md` - Os 10 comentários com pior score
- `conclusao_experimento.md` - Conclusões detalhadas do experimento
- `resumo_apresentacao.md` - Resumo executivo

### Visualizações:
- `metricas_overview.png` - Visão geral das métricas
- `comparacao_linguagens.png` - Comparação por linguagem
- `matriz_correlacao.png` - Correlações entre métricas
- `distribuicao_scores.png` - Distribuição dos scores
- `radar_performance.png` - Gráfico radar de performance
- `top_bottom_comparison.png` - Comparação top vs bottom
- `infografico_resumo.png` - Infográfico executivo

## Como Usar os Resultados

### Para Apresentação:
- Use `infografico_resumo.png` como slide principal
- Consulte `resumo_apresentacao.md` para dados-chave
- Use `radar_performance.png` para mostrar performance geral

### Para Análise Detalhada:
- Examine `conclusao_experimento.md` para insights
- Analise `top_10_melhores.md` e `top_10_piores.md` para exemplos
- Use `dados_completos.csv` para análises personalizadas

### Para Discussão:
- Foque nos resultados das 5 métricas implementadas
- Compare performance entre diferentes linguagens
- Discuta limitações e pontos fortes identificados

## Interpretação dos Scores
- **0.8 - 1.0**: Excelente
- **0.6 - 0.8**: Bom  
- **0.4 - 0.6**: Moderado
- **0.0 - 0.4**: Baixo

## Próximos Passos Sugeridos
1. Análise qualitativa manual dos comentários extremos
2. Teste com outros modelos de IA
3. Avaliação específica por domínio/contexto
4. Implementação de métricas adicionais

---
*Análise gerada automaticamente pelo sistema de avaliação de comentários*
    """
    
    try:
        with open("results_analysis/GUIA_APRESENTACAO.md", 'w', encoding='utf-8') as f:
            f.write(summary_content.strip())
        print("✅ Guia de apresentação criado!")
        return True
    except Exception as e:
        print(f"❌ Erro ao criar guia: {e}")
        return False

def main():
    """Função principal que executa todo o pipeline"""
    print("🚀 INICIANDO ANÁLISE COMPLETA DE COMENTÁRIOS")
    print("=" * 60)
    print("DeepSeek vs Desenvolvedores Humanos - Projeto gRPC")
    print("=" * 60)
    
    start_time = time.time()
    
    # Etapa 1: Instalar dependências
    if not install_requirements():
        print("❌ Falha ao instalar dependências. Abortando...")
        return
    
    # Etapa 2: Executar análise principal
    if not run_main_analysis():
        print("❌ Falha na análise principal. Abortando...")
        return
    
    # Etapa 3: Gerar visualizações
    if not generate_visualizations():
        print("⚠️ Falha ao gerar visualizações, mas continuando...")
    
    # Etapa 4: Criar resumo de apresentação
    if not create_presentation_summary():
        print("⚠️ Falha ao criar guia de apresentação, mas continuando...")
    
    # Relatório final
    end_time = time.time()
    duration = end_time - start_time
    
    print("\n" + "=" * 60)
    print("🎉 ANÁLISE COMPLETA FINALIZADA!")
    print("=" * 60)
    print(f"⏱️  Tempo total: {duration:.1f} segundos")
    print(f"📁 Resultados salvos em: results_analysis/")
    print("\n📊 ARQUIVOS DISPONÍVEIS PARA APRESENTAÇÃO:")
    print("├── 🎯 GUIA_APRESENTACAO.md (COMEÇAR AQUI)")
    print("├── 📈 infografico_resumo.png (SLIDE PRINCIPAL)")
    print("├── 📋 resumo_apresentacao.md (DADOS-CHAVE)")
    print("├── 🎭 radar_performance.png (PERFORMANCE GERAL)")
    print("├── 🏆 top_10_melhores.md (MELHORES EXEMPLOS)")
    print("├── 💥 top_10_piores.md (PIORES EXEMPLOS)")
    print("└── 📑 conclusao_experimento.md (ANÁLISE DETALHADA)")
    print("\n✨ Sua análise está pronta para apresentação!")

if __name__ == "__main__":
    main() 