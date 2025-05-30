import os
from openai import OpenAI

# Configure your API key and client
client = OpenAI(
    api_key="<DeepSeek API Key>", 
    base_url="https://api.deepseek.com"
)

# Define paths
input_root = "./grpc-no-comments"
output_root = "./grpc-result-comments"

def generate_comments_for_code(code: str) -> str:
    """Send code to DeepSeek and return code with added comments."""
    prompt = f"""Add meaningful and concise comments to the following code. Only return the updated code:

```c++
{code}
```"""  # Change language if needed

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
        if filename.endswith((".cc", ".h")):  # Add or change extensions if needed
            input_file_path = os.path.join(dirpath, filename)

            # Get relative path and build corresponding output path
            relative_path = os.path.relpath(input_file_path, input_root)
            output_file_path = os.path.join(output_root, relative_path)

            # Ensure the output subdirectory exists
            os.makedirs(os.path.dirname(output_file_path), exist_ok=True)

            with open(input_file_path, 'r', encoding='utf-8') as f:
                code = f.read()

            try:
                commented_code = generate_comments_for_code(code)
                with open(output_file_path, 'w', encoding='utf-8') as f:
                    f.write(commented_code)
                print(f"Processed: {relative_path}")
            except Exception as e:
                print(f"Failed to process {relative_path}: {e}")
