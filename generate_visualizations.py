#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Gerador de Visualizações para Análise de Comentários
Script complementar para criar gráficos e visualizações dos resultados
"""

import json
import csv
import os
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np
from typing import Dict, List

# Configuração de estilo
plt.style.use('default')
sns.set_palette("husl")

class VisualizationGenerator:
    """Classe para gerar visualizações dos resultados da análise"""
    
    def __init__(self, results_dir: str = "results_analysis"):
        self.results_dir = results_dir
        self.viz_dir = os.path.join(results_dir, "visualizations")
        os.makedirs(self.viz_dir, exist_ok=True)
        
        # Configuração do matplotlib para português
        plt.rcParams['font.size'] = 12
        plt.rcParams['figure.figsize'] = (12, 8)
    
    def load_data(self):
        """Carrega os dados dos arquivos de resultado"""
        # Carrega estatísticas gerais
        stats_file = os.path.join(self.results_dir, "estatisticas_gerais.json")
        with open(stats_file, 'r', encoding='utf-8') as f:
            self.stats = json.load(f)
        
        # Carrega dados completos
        csv_file = os.path.join(self.results_dir, "dados_completos.csv")
        self.df = pd.read_csv(csv_file)
        
        print(f"✅ Dados carregados: {len(self.df)} registros")
    
    def create_metrics_overview(self):
        """Cria gráfico de visão geral das métricas"""
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
        
        # Gráfico de barras das médias
        metrics = ['Similaridade', 'Tamanho', 'Legibilidade', 'BLEU', 'ROUGE']
        values = [
            self.stats['similarity_score']['média'],
            self.stats['length_ratio']['média'],
            self.stats['readability_score']['média'],
            self.stats['bleu_score']['média'],
            self.stats['rouge_score']['média']
        ]
        
        bars = ax1.bar(metrics, values, color=['#FF6B6B', '#4ECDC4', '#45B7D1', '#FFA07A', '#98D8C8'])
        ax1.set_title('Médias das Métricas de Avaliação', fontweight='bold')
        ax1.set_ylabel('Score (0-1)')
        ax1.set_ylim(0, 1)
        
        # Adiciona valores nas barras
        for bar, value in zip(bars, values):
            ax1.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 0.01,
                    f'{value:.3f}', ha='center', va='bottom', fontweight='bold')
        
        # Box plot das distribuições
        
        ax2.boxplot([self.df['Score_Similaridade'], self.df['Razão_Tamanho'], 
                    self.df['Score_Legibilidade'], self.df['Score_BLEU'], 
                    self.df['Score_ROUGE']], labels=metrics)
        ax2.set_title('Distribuição das Métricas', fontweight='bold')
        ax2.set_ylabel('Score (0-1)')
        ax2.tick_params(axis='x', rotation=45)
        
        plt.tight_layout()
        plt.savefig(os.path.join(self.viz_dir, 'metricas_overview.png'), dpi=300, bbox_inches='tight')
        plt.close()
        
        print("📊 Gráfico de visão geral das métricas criado")
    
    def create_language_comparison(self):
        """Cria comparação por linguagem de programação"""
        if 'Linguagem' not in self.df.columns:
            print("⚠️ Coluna 'Linguagem' não encontrada, pulando comparação por linguagem")
            return
            
        fig, axes = plt.subplots(2, 3, figsize=(18, 12))
        axes = axes.flatten()
        
        metrics = ['Score_Similaridade', 'Razão_Tamanho', 'Score_Legibilidade', 
                  'Score_BLEU', 'Score_ROUGE', 'Score_Geral']
        metric_names = ['Similaridade', 'Tamanho', 'Legibilidade', 'BLEU', 'ROUGE', 'Geral']
        
        for i, (metric, name) in enumerate(zip(metrics, metric_names)):
            if metric in self.df.columns:
                self.df.boxplot(column=metric, by='Linguagem', ax=axes[i])
                axes[i].set_title(f'{name} por Linguagem')
                axes[i].set_xlabel('Linguagem')
                axes[i].set_ylabel('Score')
        
        plt.suptitle('Comparação de Métricas por Linguagem de Programação', fontsize=16, fontweight='bold')
        plt.tight_layout()
        plt.savefig(os.path.join(self.viz_dir, 'comparacao_linguagens.png'), dpi=300, bbox_inches='tight')
        plt.close()
        
        print("📊 Gráfico de comparação por linguagem criado")
    
    def create_correlation_matrix(self):
        """Cria matriz de correlação entre as métricas"""
        metrics_cols = ['Score_Similaridade', 'Razão_Tamanho', 'Score_Legibilidade', 
                       'Score_BLEU', 'Score_ROUGE', 'Score_Geral']
        
        # Filtra apenas as colunas que existem
        available_cols = [col for col in metrics_cols if col in self.df.columns]
        
        if len(available_cols) < 2:
            print("⚠️ Colunas de métricas insuficientes para matriz de correlação")
            return
            
        correlation_matrix = self.df[available_cols].corr()
        
        plt.figure(figsize=(10, 8))
        sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', center=0,
                   square=True, linewidths=0.5)
        plt.title('Matriz de Correlação entre Métricas', fontweight='bold')
        plt.tight_layout()
        plt.savefig(os.path.join(self.viz_dir, 'matriz_correlacao.png'), dpi=300, bbox_inches='tight')
        plt.close()
        
        print("📊 Matriz de correlação criada")
    
    def create_score_distribution(self):
        """Cria histograma da distribuição dos scores gerais"""
        if 'Score_Geral' not in self.df.columns:
            print("⚠️ Coluna 'Score_Geral' não encontrada")
            return
            
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
        
        # Histograma
        ax1.hist(self.df['Score_Geral'], bins=30, alpha=0.7, color='skyblue', edgecolor='black')
        ax1.axvline(self.df['Score_Geral'].mean(), color='red', linestyle='--', 
                   label=f'Média: {self.df["Score_Geral"].mean():.3f}')
        ax1.axvline(self.df['Score_Geral'].median(), color='green', linestyle='--',
                   label=f'Mediana: {self.df["Score_Geral"].median():.3f}')
        ax1.set_title('Distribuição dos Scores Gerais', fontweight='bold')
        ax1.set_xlabel('Score Geral')
        ax1.set_ylabel('Frequência')
        ax1.legend()
        
        # Q-Q plot para verificar normalidade
        from scipy import stats
        stats.probplot(self.df['Score_Geral'], dist="norm", plot=ax2)
        ax2.set_title('Q-Q Plot (Normalidade)', fontweight='bold')
        
        plt.tight_layout()
        plt.savefig(os.path.join(self.viz_dir, 'distribuicao_scores.png'), dpi=300, bbox_inches='tight')
        plt.close()
        
        print("📊 Gráfico de distribuição de scores criado")
    
    def create_performance_radar(self):
        """Cria gráfico radar das métricas médias"""
        metrics = ['Similaridade', 'Tamanho', 'Legibilidade', 'BLEU', 'ROUGE']
        values = [
            self.stats['similarity_score']['média'],
            self.stats['length_ratio']['média'],
            self.stats['readability_score']['média'],
            self.stats['bleu_score']['média'],
            self.stats['rouge_score']['média']
        ]
        
        # Adiciona o primeiro valor no final para fechar o polígono
        values += values[:1]
        metrics += metrics[:1]
        
        # Calcula ângulos
        angles = np.linspace(0, 2 * np.pi, len(metrics), endpoint=True)
        
        fig, ax = plt.subplots(figsize=(10, 10), subplot_kw=dict(projection='polar'))
        
        # Plota o gráfico
        ax.plot(angles, values, 'o-', linewidth=2, label='DeepSeek vs Humanos')
        ax.fill(angles, values, alpha=0.25)
        
        # Configurações
        ax.set_xticks(angles[:-1])
        ax.set_xticklabels(metrics[:-1])
        ax.set_ylim(0, 1)
        ax.set_title('Radar de Performance das Métricas', fontweight='bold', pad=20)
        ax.grid(True)
        
        plt.tight_layout()
        plt.savefig(os.path.join(self.viz_dir, 'radar_performance.png'), dpi=300, bbox_inches='tight')
        plt.close()
        
        print("📊 Gráfico radar de performance criado")
    
    def create_top_bottom_comparison(self):
        """Cria comparação visual entre melhores e piores comentários"""
        if 'Score_Geral' not in self.df.columns:
            print("⚠️ Coluna 'Score_Geral' não encontrada")
            return
            
        # Pega os top 10 e bottom 10
        top_10 = self.df.nlargest(10, 'Score_Geral')
        bottom_10 = self.df.nsmallest(10, 'Score_Geral')
        
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 8))
        
        # Top 10
        ax1.barh(range(10), top_10['Score_Geral'].values[::-1], color='green', alpha=0.7)
        ax1.set_yticks(range(10))
        ax1.set_yticklabels([f"#{i+1}" for i in range(10)])
        ax1.set_title('Top 10 Melhores Comentários', fontweight='bold')
        ax1.set_xlabel('Score Geral')
        
        # Bottom 10
        ax2.barh(range(10), bottom_10['Score_Geral'].values, color='red', alpha=0.7)
        ax2.set_yticks(range(10))
        ax2.set_yticklabels([f"#{i+1}" for i in range(10)])
        ax2.set_title('Top 10 Piores Comentários', fontweight='bold')
        ax2.set_xlabel('Score Geral')
        
        plt.tight_layout()
        plt.savefig(os.path.join(self.viz_dir, 'top_bottom_comparison.png'), dpi=300, bbox_inches='tight')
        plt.close()
        
        print("📊 Gráfico de comparação top/bottom criado")
    
    def create_summary_infographic(self):
        """Cria infográfico resumo dos principais achados"""
        fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
        
        # 1. Score geral médio (gauge)
        score_geral = self.stats['overall_score']['média']
        ax1.pie([score_geral, 1-score_geral], colors=['#4CAF50', '#E0E0E0'], 
               startangle=90, counterclock=False)
        ax1.add_patch(plt.Circle((0,0), 0.7, color='white'))
        ax1.text(0, 0, f'{score_geral:.3f}', ha='center', va='center', 
                fontsize=24, fontweight='bold')
        ax1.text(0, -0.3, 'Score Geral', ha='center', va='center', fontsize=12)
        ax1.set_title('Performance Geral da IA', fontweight='bold')
        
        # 2. Melhor métrica
        best_metric = max(self.stats.items(), key=lambda x: x[1]['média'] if x[0] != 'overall_score' else 0)
        metrics_names = {'similarity_score': 'Similaridade', 'length_ratio': 'Tamanho',
                        'readability_score': 'Legibilidade', 'bleu_score': 'BLEU',
                        'rouge_score': 'ROUGE'}
        
        ax2.bar(['Melhor\nMétrica'], [best_metric[1]['média']], color='#2196F3', width=0.5)
        ax2.set_ylim(0, 1)
        ax2.set_title(f'Melhor Métrica: {metrics_names.get(best_metric[0], best_metric[0])}', 
                     fontweight='bold')
        ax2.text(0, best_metric[1]['média'] + 0.05, f'{best_metric[1]["média"]:.3f}', 
                ha='center', fontweight='bold')
        
        # 3. Total de comentários analisados
        total_comments = len(self.df)
        ax3.text(0.5, 0.5, f'{total_comments:,}', ha='center', va='center', 
                fontsize=36, fontweight='bold', transform=ax3.transAxes)
        ax3.text(0.5, 0.3, 'Comentários\nAnalisados', ha='center', va='center', 
                fontsize=14, transform=ax3.transAxes)
        ax3.set_xlim(0, 1)
        ax3.set_ylim(0, 1)
        ax3.axis('off')
        ax3.set_title('Volume de Dados', fontweight='bold')
        
        # 4. Linguagens analisadas
        if 'Linguagem' in self.df.columns:
            lang_counts = self.df['Linguagem'].value_counts()
            ax4.pie(lang_counts.values, labels=lang_counts.index, autopct='%1.1f%%')
            ax4.set_title('Distribuição por Linguagem', fontweight='bold')
        else:
            ax4.text(0.5, 0.5, 'C++\nPython\nRuby', ha='center', va='center', 
                    fontsize=16, transform=ax4.transAxes)
            ax4.set_title('Linguagens Avaliadas', fontweight='bold')
            ax4.axis('off')
        
        plt.suptitle('RESUMO EXECUTIVO - ANÁLISE DE COMENTÁRIOS IA vs HUMANOS', 
                    fontsize=16, fontweight='bold', y=0.98)
        plt.tight_layout()
        plt.savefig(os.path.join(self.viz_dir, 'infografico_resumo.png'), dpi=300, bbox_inches='tight')
        plt.close()
        
        print("📊 Infográfico resumo criado")
    
    def generate_all_visualizations(self):
        """Gera todas as visualizações"""
        print("🎨 Gerando visualizações...")
        
        try:
            self.load_data()
            
            self.create_metrics_overview()
            self.create_language_comparison()
            self.create_correlation_matrix()
            self.create_score_distribution()
            self.create_performance_radar()
            self.create_top_bottom_comparison()
            self.create_summary_infographic()
            
            print(f"\n✅ Todas as visualizações foram salvas em: {self.viz_dir}/")
            print("\nVisualizações criadas:")
            print("├── metricas_overview.png")
            print("├── comparacao_linguagens.png")
            print("├── matriz_correlacao.png")
            print("├── distribuicao_scores.png")
            print("├── radar_performance.png")
            print("├── top_bottom_comparison.png")
            print("└── infografico_resumo.png")
            
        except Exception as e:
            print(f"❌ Erro ao gerar visualizações: {e}")

if __name__ == "__main__":
    visualizer = VisualizationGenerator()
    visualizer.generate_all_visualizations()