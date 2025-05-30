# Script para remover todos os arquivos .bak de um diretório e subdiretórios.

param (
    [string]$DiretorioAlvo = (Get-Location).Path,
    [switch]$DryRun, # Apenas lista os arquivos que seriam deletados, sem deletar
    [switch]$Forcar # Deleta sem pedir confirmação (após listar os arquivos)
)

Write-Host "Procurando arquivos .bak em: '$($DiretorioAlvo)' e suas subpastas..."
Write-Host "---------------------------------------------------------------"

try {
    # Get-ChildItem -Filter é geralmente case-insensitive no Windows para extensões
    $arquivosBak = Get-ChildItem -Path $DiretorioAlvo -Recurse -File -Filter "*.bak" -ErrorAction SilentlyContinue

    if ($null -eq $arquivosBak -or $arquivosBak.Count -eq 0) {
        Write-Host "Nenhum arquivo .bak encontrado no diretório '$($DiretorioAlvo)'."
        exit
    }

    Write-Host "Arquivos .bak encontrados:"
    $arquivosBak | ForEach-Object { Write-Host $_.FullName }
    Write-Host "---------------------------------------------------------------"
    Write-Host "Total de arquivos .bak encontrados: $($arquivosBak.Count)"
    Write-Host ""

    if ($DryRun) {
        Write-Warning "MODO DRY RUN (SIMULAÇÃO): Nenhum arquivo será excluído."
        exit
    }

    if (-not $Forcar) {
        $confirmacao = Read-Host "TEM CERTEZA que deseja excluir os $($arquivosBak.Count) arquivo(s) .bak listados acima? (s/N)"
        if ($confirmacao.ToLower() -ne 's') {
            Write-Host "Operação cancelada pelo usuário."
            exit
        }
    }

    Write-Host "Excluindo arquivos .bak..."
    $erros = 0
    $sucessos = 0

    foreach ($arquivo in $arquivosBak) {
        try {
            Remove-Item -Path $arquivo.FullName -Force -ErrorAction Stop
            Write-Host "Excluído: $($arquivo.FullName)"
            $sucessos++
        }
        catch {
            Write-Error "Falha ao excluir $($arquivo.FullName): $($_.Exception.Message)"
            $erros++
        }
    }

    Write-Host "---------------------------------------------------------------"
    Write-Host "Operação concluída."
    Write-Host "Arquivos .bak excluídos com sucesso: $sucessos"
    if ($erros -gt 0) {
        Write-Warning "Falhas ao excluir: $erros"
    }
    Write-Host "---------------------------------------------------------------"

}
catch {
    Write-Error "Ocorreu um erro geral: $($_.Exception.Message)"
    Write-Warning "Verifique se o caminho do diretório está correto e se você tem permissão para acessá-lo e excluir arquivos."
}
