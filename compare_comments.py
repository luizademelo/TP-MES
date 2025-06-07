import os
import re

original_dir = "grpc-original"
ai_dir = "grpc-result-comments-cc"
MAX_PAIRS = 2000

def get_all_files(directory):
    all_files = set()
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.cc', '.h')):
                rel_path = os.path.relpath(os.path.join(root, file), start=directory)
                all_files.add(rel_path)
    return all_files

def extract_comments(file_path):
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        code = f.read()
    line_comments = re.findall(r'//.*', code)
    block_comments = re.findall(r'/\*[\s\S]*?\*/', code)
    return line_comments + block_comments

original_files = get_all_files(original_dir)
ai_files = get_all_files(ai_dir)
matched_files = list(original_files & ai_files)

print(f"Matched {len(matched_files)} files with comments")

pair_count = 0

for filename in matched_files:
    if pair_count >= MAX_PAIRS:
        break

    orig_path = os.path.join(original_dir, filename)
    ai_path = os.path.join(ai_dir, filename)

    human_comments = extract_comments(orig_path)
    ai_comments = extract_comments(ai_path)

    min_len = min(len(human_comments), len(ai_comments))

    for i in range(min_len):
        if pair_count >= MAX_PAIRS:
            break

        print(f"\nFile: {filename} — Comment Pair #{pair_count + 1}")
        print("-" * 50)
        print(f"🧠 Human:    {human_comments[i].strip()}")
        print(f"🤖 AI:       {ai_comments[i].strip()}")
        print("-" * 50)

        pair_count += 1

if pair_count == 0:
    print("⚠️ No comments to compare.")
else:
    print(f"\n✅ Displayed {pair_count} comment pairs.")
