import os
import sys
import re
import shutil
import argparse
import glob

# Definir as extensões por categoria de estilo de comentário
C_STYLE_EXTENSIONS = {'.0', '.1', '.3', '.4', '.5', '.9', '.c', '.c++', '.cc', '.cpp', '.cs', '.h', '.hpp', 
                  '.java', '.js', '.m', '.mm', '.swift', '.objc', '.go', '.proto', '.gradle', 
                  '.css', '.def', '.php', '.base', '.core', '.inc', '.include', '.internal', 
                  '.clang', '.attr', '.client', '.server', '.xds_client', '.xds_server'}

PYTHON_STYLE_EXTENSIONS = {'.py', '.pyi', '.pyx', '.pxd', '.pxi', '.bzl', '.bazel', '.awk', '.rb', 
                       '.build', '.gemspec', '.modulemap'}

SHELL_STYLE_EXTENSIONS = {'.sh', '.bash', '.bazelrc', '.gitignore', '.dockerignore', '.clang-format', 
                      '.clang-tidy', '.config', '.conf', '.cnf', '.cfg', '.rc', '.properties', 
                      '.toml', '.yaml', '.yml', '.gitattributes', '.editorconfig', '.gcloudignore',
                      '.bazelignore', '.bazelversion', '.yapfignore', '.git-blame-ignore-revs',
                      '.gitmodules', '.gitallowed', '.current_version', '.r0', '.pylintrc', 
                      '.pylintrc-examples', '.pylintrc-tests', '.yardopts', '.in', '.dockerfile',
                      '.listimagesrequired', '.rspec'}

XML_STYLE_EXTENSIONS = {'.html', '.xml', '.svg', '.xsl', '.plist', '.storyboard', '.xcscheme', 
                    '.xcworkspacedata', '.csproj', '.props', '.targets', '.sln', '.pbxproj'}

SPECIAL_EXTENSIONS = {'.json', '.md', '.rst', '.txt', '.template', '.tpl', '.mako', '.inja', '.cmake',
                  '.lock', '.list', '.jar', '.bin', '.pdf', '.png', '.patch', '.pub', '.key',
                  '.pem', '.crt', '.crl', '.headers', '.ps1', '.old', '.mod', '.podspec', '.pro',
                  '.stylecop', '.entitlements', '.w32', '.x', '.xcprivacy', '.istio_echo_server', '.snk'}

# Combinar todas as extensões
ALL_SUPPORTED_EXTENSIONS = (C_STYLE_EXTENSIONS | PYTHON_STYLE_EXTENSIONS | 
                        SHELL_STYLE_EXTENSIONS | XML_STYLE_EXTENSIONS | SPECIAL_EXTENSIONS)

def determine_comment_style(file_ext):
 """Determina o estilo de comentário baseado na extensão do arquivo"""
 ext = file_ext.lower()
 
 if ext in C_STYLE_EXTENSIONS:
     return "c_style"
 elif ext in PYTHON_STYLE_EXTENSIONS:
     return "python_style"
 elif ext in SHELL_STYLE_EXTENSIONS:
     return "shell_style"
 elif ext in XML_STYLE_EXTENSIONS:
     return "xml_style"
 elif ext in SPECIAL_EXTENSIONS:
     return "special"
 else:
     return None

def should_preserve_comment(line, is_first_comment_block=False, file_ext=None):
 """Determina se um comentário deve ser preservado"""
 # Preservar shebang
 if line.strip().startswith('#!'):
     return True
 
 # Preservar cabeçalhos de licença/copyright
 if is_first_comment_block and any(keyword in line.lower() for keyword in 
                                  ['copyright', 'license', 'permission', 'author']):
     return True
     
 # Preservar comentários importantes nos arquivos python
 if file_ext in PYTHON_STYLE_EXTENSIONS or file_ext in SHELL_STYLE_EXTENSIONS:
     # Preservar notas importantes
     if re.search(r'#\s*(note|todo|fixme|hack|xxx|important):', line.lower()):
         return True
 
 # Preservar comentários importantes em arquivos C-style
 if file_ext in C_STYLE_EXTENSIONS:
     if re.search(r'//\s*(note|todo|fixme|hack|xxx|important):', line.lower()) or \
        re.search(r'/\*\s*(note|todo|fixme|hack|xxx|important):', line.lower()):
         return True
 
 return False

def remove_comments_c_style(content, filename):
 """Remove comentários de linguagens estilo C (C, C++, Java, Go, etc.) preservando comentários importantes"""
 _, ext = os.path.splitext(filename)
 result = []
 i = 0
 in_string = False
 in_char = False
 in_single_comment = False
 in_multi_comment = False
 string_char = None
 is_first_comment_block = True
 comment_buffer = []
 
 while i < len(content):
     # Não estamos em modo de comentário - verificar início de string ou comentário
     if not in_single_comment and not in_multi_comment:
         # Processamento de strings
         if not in_string and not in_char and (content[i] == '"' or content[i] == "'"):
             string_char = content[i]
             if content[i] == "'":
                 in_char = True
             else:
                 in_string = True
             result.append(content[i])
         # Fim da string
         elif (in_string and content[i] == '"' and string_char == '"') or (in_char and content[i] == "'" and string_char == "'"):
             if i == 0 or content[i-1] != '\\': # Verificar aspas escapadas
                 in_string = False
                 in_char = False
                 string_char = None
             result.append(content[i])
         # Início de comentário de linha única
         elif not in_string and not in_char and i < len(content) - 1 and content[i:i+2] == '//':
             in_single_comment = True
             comment_buffer = [content[i]]
             i += 1  # Pular o segundo '/'
             comment_buffer.append(content[i])
         # Início de comentário de múltiplas linhas
         elif not in_string and not in_char and i < len(content) - 1 and content[i:i+2] == '/*':
             in_multi_comment = True
             comment_buffer = [content[i]]
             i += 1  # Pular o '*'
             comment_buffer.append(content[i])
         # Código regular
         else:
             result.append(content[i])
     
     # Em modo de comentário de linha única
     elif in_single_comment:
         comment_buffer.append(content[i])
         if content[i] == '\n':
             # Verificar se é um comentário para preservar
             comment_str = ''.join(comment_buffer)
             if should_preserve_comment(comment_str, is_first_comment_block, ext):
                 result.extend(comment_buffer)
                 is_first_comment_block = False
             else:
                 result.append('\n')  # Manter a quebra de linha
             in_single_comment = False
             comment_buffer = []
     
     # Em modo de comentário de múltiplas linhas
     elif in_multi_comment:
         comment_buffer.append(content[i])
         if i < len(content) - 1 and content[i:i+2] == '*/':
             comment_buffer.append(content[i+1])
             # Verificar se é um comentário para preservar
             comment_str = ''.join(comment_buffer)
             if should_preserve_comment(comment_str, is_first_comment_block, ext):
                 result.extend(comment_buffer)
                 is_first_comment_block = False
             else:
                 # Preservar quebras de linha para manter a estrutura do arquivo
                 for char in comment_buffer:
                     if char == '\n':
                         result.append(char)
             in_multi_comment = False
             i += 1  # Pular o '/'
             comment_buffer = []
         elif content[i] == '\n':
             result.append('\n')  # Manter a estrutura de linhas
     
     i += 1
 
 return ''.join(result)

def remove_comments_python(content, filename):
 """Remove comentários de código Python preservando comentários importantes"""
 lines = content.split('\n')
 result_lines = []
 in_triple_quotes = False
 triple_char = None
 is_first_comment_block = True
 comment_block = []
 
 # Processamento especial para arquivos de configuração
 if os.path.basename(filename) in ['setup.py', 'requirements.txt', 'Makefile', 'CMakeLists.txt']:
     return content
 
 i = 0
 while i < len(lines):
     line = lines[i]
     
     # Verificar docstrings de múltiplas linhas
     if not in_triple_quotes and ('"""' in line or "'''" in line):
         # Determinar qual tipo de aspas triplas
         if '"""' in line and not in_triple_quotes:
             triple_char = '"""'
             in_triple_quotes = True
         elif "'''" in line and not in_triple_quotes:
             triple_char = "'''"
             in_triple_quotes = True
             
         # Se abre e fecha na mesma linha
         if line.count(triple_char) >= 2:
             result_lines.append(line)
             in_triple_quotes = False
         else:
             result_lines.append(line)
         
     # Continuar docstring de múltiplas linhas
     elif in_triple_quotes:
         result_lines.append(line)
         if triple_char in line:
             in_triple_quotes = False
     
     # Linha normal - processa comentários
     else:
         # Procurar por comentários na linha
         code_part = line
         comment_part = ""
         
         # Analisar se há comentário na linha
         in_string = False
         string_char = None
         comment_pos = -1
         
         for pos, char in enumerate(line):
             # Lidar com strings
             if char in ["'", '"'] and (pos == 0 or line[pos-1] != '\\'):
                 if not in_string:
                     in_string = True
                     string_char = char
                 elif string_char == char:
                     in_string = False
             
             # Encontrar comentário
             if char == '#' and not in_string:
                 comment_pos = pos
                 break
                 
         # Se encontrou comentário
         if comment_pos != -1:
             code_part = line[:comment_pos]
             comment_part = line[comment_pos:]
             
             # Verificar se é um comentário para preservar
             if should_preserve_comment(comment_part, is_first_comment_block, os.path.splitext(filename)[1]):
                 result_lines.append(line)  # Manter a linha completa
             else:
                 if code_part.strip():
                     result_lines.append(code_part)  # Adicionar apenas a parte de código
                 else:
                     result_lines.append("")  # Linha em branco para manter a estrutura
         else:
             result_lines.append(line)
             
         # Atualizar flag de primeiro bloco de comentário
         if comment_part and is_first_comment_block:
             # Se não for mais o bloco inicial (linha em branco ou código)
             if not line.strip() or (code_part.strip() and not code_part.strip().startswith('#')):
                 is_first_comment_block = False
     
     i += 1
 
 return '\n'.join(result_lines)

def remove_comments_shell(content, filename):
 """Remove comentários de scripts Shell/Bash/Config preservando comentários importantes"""
 result = []
 lines = content.split('\n')
 is_first_comment_block = True
 
 for line_num, line in enumerate(lines):
     # Verificar shebang no início do arquivo
     if line_num == 0 and line.startswith('#!'):
         result.append(line)
         continue
         
     # Processar linha para comentários
     in_string = False
     string_char = None
     comment_pos = -1
     
     for i, char in enumerate(line):
         # Processar literais de string
         if char in ['"', "'", '`'] and (i == 0 or line[i-1] != '\\'):
             if not in_string:
                 in_string = True
                 string_char = char
             elif string_char == char:
                 in_string = False
                 string_char = None
         
         # Encontrar início de comentário fora de strings
         if char == '#' and not in_string:
             comment_pos = i
             break
     
     # Verificar se o comentário deve ser preservado
     if comment_pos != -1:
         comment_part = line[comment_pos:]
         code_part = line[:comment_pos]
         
         if should_preserve_comment(comment_part, is_first_comment_block, os.path.splitext(filename)[1]):
             result.append(line)  # Manter a linha completa
         else:
             if code_part.strip():
                 result.append(code_part)  # Manter apenas o código
             else:
                 result.append("")  # Linha em branco para manter estrutura
                 
         # Se esta linha tinha apenas comentário e a próxima tem código, não é mais o bloco inicial
         if not code_part.strip() and line_num + 1 < len(lines) and not lines[line_num + 1].lstrip().startswith('#'):
             is_first_comment_block = False
     else:
         result.append(line)
         # Se encontramos uma linha de código, o bloco inicial de comentários terminou
         if line.strip() and is_first_comment_block:
             is_first_comment_block = False
 
 return '\n'.join(result)

def remove_comments_xml(content, filename):
 """Remove comentários de arquivos XML/HTML preservando comentários importantes"""
 in_comment = False
 comment_start = -1
 result = []
 i = 0
 
 while i < len(content):
     # Início de comentário
     if not in_comment and i < len(content) - 3 and content[i:i+4] == "<!--":
         in_comment = True
         comment_start = i
         i += 4  # Pular o marcador de comentário
     # Fim de comentário
     elif in_comment and i < len(content) - 2 and content[i:i+3] == "-->":
         comment_text = content[comment_start:i+3]
         # Verificar se é um comentário para preservar
         if should_preserve_comment(comment_text, True, os.path.splitext(filename)[1]):
             result.append(comment_text)
             
         i += 3  # Pular o marcador de fim de comentário
         in_comment = False
     # Conteúdo regular
     elif not in_comment:
         result.append(content[i])
         i += 1
     # Dentro de comentário
     else:
         i += 1
 
 return ''.join(result)

def remove_extra_whitespace(content):
 """Remove espaços em branco extras do conteúdo"""
 # Remove espaços em branco no final das linhas
 lines = content.split('\n')
 trimmed_lines = [line.rstrip() for line in lines]
 
 # Remove linhas em branco consecutivas (mantém apenas uma)
 result_lines = []
 prev_empty = False
 for line in trimmed_lines:
     if not line:  # Linha vazia
         if not prev_empty:
             result_lines.append(line)
             prev_empty = True
     else:
         result_lines.append(line)
         prev_empty = False
 
 return '\n'.join(result_lines)

def should_skip_file(file_path):
 """Determina se um arquivo deve ser ignorado"""
 basename = os.path.basename(file_path)
 
 # Lista de arquivos a ignorar
 skip_files = [
     'setup.py',
     'MANIFEST.in',
     'README',
     'README.md',
     'LICENSE',
     'COPYING',
     'NOTICE'
 ]
 
 # Verificar nomes específicos
 if basename in skip_files:
     return True
 
 # Verificar padrões de nome
 if any(pattern in basename.lower() for pattern in ['license', 'copyright', 'readme', 'changelog']):
     return True
 
 # Verificar extensões específicas que não devem ser processadas
 _, ext = os.path.splitext(file_path)
 if ext.lower() in ['.pdf', '.png', '.jar', '.bin']:
     return True
 
 return False

def process_file(file_path, make_backup=True, remove_whitespace=False, backup_files=None):
 """Processa um arquivo para remover comentários com base em sua extensão"""
 _, ext = os.path.splitext(file_path)
 ext = ext.lower()
 
 # Verificar se o arquivo deve ser ignorado
 if should_skip_file(file_path):
     print(f"Ignorando arquivo: {file_path} (arquivo de configuração/licença/binário)")
     return
 
 # Ignorar o próprio script
 if os.path.basename(file_path) == "remove_comments.py":
     print(f"Ignorando o próprio script: {file_path}")
     return
 
 try:
     # Fazer backup se solicitado
     backup_path = None
     if make_backup:
         backup_path = file_path + '.bak'
         shutil.copyfile(file_path, backup_path)
         if backup_files is not None:
             backup_files.append(backup_path)
         print(f"Backup criado: {backup_path}")
     
     try:
         with open(file_path, 'r', encoding='utf-8') as f:
             content = f.read()
     except UnicodeDecodeError:
         # Tentar com outra codificação ou ignorar erros
         try:
             with open(file_path, 'r', encoding='latin-1') as f:
                 content = f.read()
         except:
             print(f"Erro ao ler o arquivo: {file_path} - Pulando...")
             if make_backup:
                 os.remove(backup_path)
                 if backup_files and backup_path in backup_files:
                     backup_files.remove(backup_path)
             return
     
     # Verificar se o arquivo está vazio
     if not content.strip():
         print(f"Arquivo vazio: {file_path}")
         if make_backup:
             os.remove(backup_path)
             if backup_files and backup_path in backup_files:
                 backup_files.remove(backup_path)
         return
     
     # Determinar o estilo de comentário
     comment_style = determine_comment_style(ext)
     
     if comment_style == "c_style":
         modified_content = remove_comments_c_style(content, file_path)
     elif comment_style == "python_style":
         modified_content = remove_comments_python(content, file_path)
     elif comment_style == "shell_style":
         modified_content = remove_comments_shell(content, file_path)
     elif comment_style == "xml_style":
         modified_content = remove_comments_xml(content, file_path)
     elif comment_style == "special":
         # Para formatos especiais, simplesmente manter o conteúdo original
         modified_content = content
     else:
         print(f"Tipo de arquivo não suportado: {ext} para o arquivo {file_path}")
         if make_backup and backup_path:
             os.remove(backup_path)
             if backup_files and backup_path in backup_files:
                 backup_files.remove(backup_path)
         return
     
     # Remover espaços em branco extras se solicitado
     if remove_whitespace:
         modified_content = remove_extra_whitespace(modified_content)
     
     # Verificar se houve alterações
     if content == modified_content:
         print(f"Nenhuma alteração em: {file_path}")
         if make_backup and backup_path:
             os.remove(backup_path)
             if backup_files and backup_path in backup_files:
                 backup_files.remove(backup_path)
         return
     
     # Escrever o conteúdo modificado de volta para o arquivo
     with open(file_path, 'w', encoding='utf-8') as f:
         f.write(modified_content)
     
     print(f"Arquivo processado: {file_path} - Removido: {'comentários' + (' e espaços em branco' if remove_whitespace else '')}")
 
 except Exception as e:
     print(f"Erro ao processar {file_path}: {str(e)}")
     # Em caso de erro, tentar restaurar o backup
     if make_backup and backup_path and os.path.exists(backup_path):
         try:
             shutil.copyfile(backup_path, file_path)
             print(f"Arquivo restaurado a partir do backup após erro: {file_path}")
         except Exception:
             print(f"Erro ao restaurar backup para {file_path}")

def remove_all_backups(directory):
 """Remove todos os arquivos de backup (.bak) em um diretório recursivamente"""
 count = 0
 print("\nRemovendo todos os arquivos de backup...")
 
 # Para um diretório, buscar recursivamente
 if os.path.isdir(directory):
     for root, _, _ in os.walk(directory):
         for backup_file in glob.glob(os.path.join(root, "*.bak")):
             try:
                 os.remove(backup_file)
                 print(f"Backup removido: {backup_file}")
                 count += 1
             except Exception as e:
                 print(f"Erro ao remover backup {backup_file}: {str(e)}")
 # Para um arquivo único
 elif os.path.isfile(directory + '.bak'):
     try:
         os.remove(directory + '.bak')
         print(f"Backup removido: {directory + '.bak'}")
         count += 1
     except Exception as e:
         print(f"Erro ao remover backup {directory + '.bak'}: {str(e)}")
         
 print(f"Total de {count} arquivos de backup removidos.")
 return count

def process_directory(directory, make_backup=True, remove_whitespace=False, remove_backups=False):
 """Processa todos os arquivos suportados em um diretório"""
 backup_files = [] if make_backup else None
 
 for root, _, files in os.walk(directory):
     for file in files:
         file_path = os.path.join(root, file)
         _, ext = os.path.splitext(file_path)
         if ext.lower() in ALL_SUPPORTED_EXTENSIONS:
             process_file(file_path, make_backup, remove_whitespace, backup_files)
 
 # Remover backups se solicitado - usando a função específica para garantir que todos sejam removidos
 if make_backup and remove_backups:
     remove_all_backups(directory)

def main():
 """Função principal para executar o script."""
 # Configurar parser de argumentos
 parser = argparse.ArgumentParser(description='Remove comentários e espaços em branco de arquivos de código fonte.')
 parser.add_argument('path', nargs='?', default=None, help='Caminho do diretório ou arquivo a ser processado. Se não fornecido, usa o diretório do script.')
 parser.add_argument('--no-backup', action='store_true', help='Não criar arquivos de backup')
 parser.add_argument('--remove-backups', action='store_true', help='Remover arquivos de backup após conclusão bem-sucedida')
 parser.add_argument('--remove-whitespace', action='store_true', help='Também remover espaços em branco extras (final de linhas e linhas em branco consecutivas)')
 parser.add_argument('--clean-backups', action='store_true', help='Apenas remover arquivos .bak existentes sem processar arquivos')
 
 args = parser.parse_args()
 
 # Determinar o caminho a ser processado
 script_dir = os.path.dirname(os.path.abspath(__file__))
 path = args.path if args.path else script_dir
 
 # Opção para apenas limpar backups
 if args.clean_backups:
     print(f"Modo de limpeza: removendo apenas arquivos .bak em {path}")
     remove_all_backups(path)
     return
 
 # Configurar opções
 make_backup = not args.no_backup
 remove_backups = args.remove_backups
 remove_whitespace = args.remove_whitespace
 
 print(f"Caminho a processar: {path}")
 print(f"Modo de backup: {'DESATIVADO' if args.no_backup else 'ATIVADO'}")
 if make_backup:
     print(f"Remoção de backups após execução: {'ATIVADO' if remove_backups else 'DESATIVADO'}")
 print(f"Remoção de espaços em branco: {'ATIVADO' if remove_whitespace else 'DESATIVADO'}")
 print(f"Total de extensões suportadas: {len(ALL_SUPPORTED_EXTENSIONS)}")
 
 if os.path.isdir(path):
     process_directory(path, make_backup, remove_whitespace, remove_backups)
 elif os.path.isfile(path):
     backup_files = [] if make_backup else None
     process_file(path, make_backup, remove_whitespace, backup_files)
     # Remover backups se solicitado
     if make_backup and remove_backups:
         remove_all_backups(os.path.dirname(path))
 else:
     print(f"Caminho não encontrado: {path}")

if __name__ == "__main__":
 main()
