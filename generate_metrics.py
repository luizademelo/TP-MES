import os
import re
from nltk.translate.bleu_score import sentence_bleu, SmoothingFunction
from nltk.translate.meteor_score import meteor_score
from rouge_score import rouge_scorer
import nltk
nltk.download('wordnet')

# Directories
original_dir = "grpc-original"
ai_dir = "grpc-result-comments-cc"

# Recursively collect all .cc and .h files with relative paths
def get_all_files(directory):
    all_files = set()
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.cc', '.h')):
                rel_path = os.path.relpath(os.path.join(root, file), start=directory)
                all_files.add(rel_path)
    return all_files

original_files = get_all_files(original_dir)
ai_files = get_all_files(ai_dir)

matched_files = list(original_files & ai_files)
print(f"Matched {len(matched_files)} files")

# Function to extract line and block comments
def extract_comments(file_path):
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        code = f.read()
    line_comments = re.findall(r'//.*', code)
    block_comments = re.findall(r'/\*[\s\S]*?\*/', code)
    return line_comments + block_comments

# Metric setup
smoothie = SmoothingFunction().method4
rouge = rouge_scorer.RougeScorer(['rouge1', 'rougeL'], use_stemmer=True)

# Score lists
bleu_scores = []
meteor_scores = []
rouge1_scores = []
rougeL_scores = []

# Compare comments
for filename in matched_files:
    original_file = os.path.join(original_dir, filename)
    ai_file = os.path.join(ai_dir, filename)

    human_comments = extract_comments(original_file)
    ai_comments = extract_comments(ai_file)

    min_len = min(len(human_comments), len(ai_comments))

    for i in range(min_len):
        ref = human_comments[i].strip()
        hyp = ai_comments[i].strip()

        ref_tokens = ref.split()
        hyp_tokens = hyp.split()

        # BLEU
        bleu = sentence_bleu([ref_tokens], hyp_tokens, smoothing_function=smoothie)
        bleu_scores.append(bleu)

        # METEOR
        meteor = meteor_score([ref_tokens], hyp_tokens)
        meteor_scores.append(meteor)

        # ROUGE
        r = rouge.score(ref, hyp)
        rouge1_scores.append(r["rouge1"].fmeasure)
        rougeL_scores.append(r["rougeL"].fmeasure)

# Output results
if bleu_scores:
    print("\n--- Evaluation Results ---")
    print(f"BLEU:     {sum(bleu_scores)/len(bleu_scores):.4f}")
    print(f"METEOR:   {sum(meteor_scores)/len(meteor_scores):.4f}")
    print(f"ROUGE-1:  {sum(rouge1_scores)/len(rouge1_scores):.4f}")
    print(f"ROUGE-L:  {sum(rougeL_scores)/len(rougeL_scores):.4f}")
else:
    print("⚠️ No matching comments found to evaluate.")
