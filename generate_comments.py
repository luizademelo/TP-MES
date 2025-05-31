import os
from openai import OpenAI

# Configure your API key and client
client = OpenAI(
    api_key="",  # Be careful with hardcoding API keys!
    base_url="https://api.deepseek.com"
)

# Define paths
input_root = "./grpc-no-comments"
output_root = "./grpc-result-comments"

def generate_comments_for_code(code: str) -> str:
    """Send code to DeepSeek and return code with added comments."""
    prompt = (
        "You are a senior developer specializing in software maintenance and evolution. "
        "Your task is to document code snippets by generating comments that are clear, accurate, "
        "and helpful for future developers. To do this, you must analyze the provided code and "
        "produce comments that explain the logic and implemented functionalities. Only return the updated code with comments."
        "The code snippet you should comment is:\n\n"
        f"```c++\n{code}\n```"
    )

    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=[
            {"role": "system", "content": "You are a helpful assistant that comments code."},
            {"role": "user", "content": prompt},
        ],
        stream=False
    )
    return response.choices[0].message.content.strip()

# Recursively walk through input directory
for dirpath, dirnames, filenames in os.walk(input_root):
    for filename in filenames:
        if filename.endswith((".cc", ".h")):
            input_file_path = os.path.join(dirpath, filename)

            # Build relative path and output path
            relative_path = os.path.relpath(input_file_path, input_root)
            output_file_path = os.path.join(output_root, relative_path)

            # Create subdirectory if it doesn't exist
            os.makedirs(os.path.dirname(output_file_path), exist_ok=True)

            # Read input code
            with open(input_file_path, 'r', encoding='utf-8') as f:
                code = f.read()

            # Skip empty files to avoid wasting tokens
            if not code.strip():
                print(f"Skipped empty file: {relative_path}")
                continue

            try:
                commented_code = generate_comments_for_code(code)
                with open(output_file_path, 'w', encoding='utf-8') as f:
                    f.write(commented_code)
                print(f"✅ Processed: {relative_path}")
            except Exception as e:
                print(f"❌ Failed to process {relative_path}: {e}")
