# Trabalho Prático 2 - Manutenção e Evolução de Software

## Membros do grupo
- Henrique Lucas Gomes Rezende
- Joao Vitor Ferreira
- Lucas Roberto Santos Avelar
- Luiza de Melo Gomes

## Objetivo do trabalho
O objetivo deste trabalho é comparar comentários de código gerados por inteligência artificial com aqueles escritos por humanos, analisando aspectos como clareza, utilidade, precisão e aderência às boas práticas de documentação. A partir dessa comparação, pretende-se avaliar a eficácia dos modelos de IA na geração de comentários compreensíveis e úteis para manutenção e entendimento de programas, identificando seus pontos fortes, limitações e possíveis melhorias.

## Metodologia
### Modelo de linguagem que será usado
DeepSeek API

### Datasets (número e critérios de seleção dos sistemas)

O sistema que será utilizado será o GRPC do Google, por conta da ampla quantidade de arquivos: https://github.com/grpc/grpc. Há pelo menos 100 arquivos de código fonte por implementação em uma linguagem do GRPC. 

Você é um desenvolvedor senior de manutenção e evolução de software. Sua tarefa é criar a documentação de trechos de código, gerando comentários que sejam claros, precisos e úteis para futuros desenvolvedores. Para tanto, você deverá analisar um código fornecido e produzir comentários que expliquem a lógica e as funcionalidades implementadas. O trecho de código que você deverá gerar os comentários é este

```python
print("Hello World”)
```
E você pode retornar criar um novo arquivo com a mesma estrutura de diretório em ‘xxx’


### Avaliação quantitativa (como será feita)
- Será utilizada uma métrica que mensure a quantidade de caracteres (ou diferenças em blocos de texto) entre os comentários originais e os gerados pela IA.
- Será implementado um script para computar a diferença percentual entre os textos dos comentários para cada trecho avaliado.

### Avaliação qualitativa (como será feita)
- Avaliar os comentários mais discrepantes em relação ao original 
- Verificar se os comentários gerados pela IA contém anti-padrões
- Analisar se os comentários explicam adequadamente a lógica do código.
- Verificar se os comentários servem para facilitar a manutenção e compreensão do código.
- Confirmar se os comentários abordam corretamente as funcionalidades e decisões implementadas.
- Aderência às Boas Práticas: Comparar com padrões recomendados (comentários concisos, com explicações sobre o “porquê” e não somente o “o quê”).


