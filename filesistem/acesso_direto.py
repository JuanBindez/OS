import time

numero_linha = int(input("Digite o número da linha que deseja ler: "))

inicio = time.time()

# Abre o arquivo e lê a linha específica
with open('dados.txt', 'r') as arquivo:
    linhas = arquivo.readlines()
    if numero_linha <= len(linhas):
        print(linhas[numero_linha - 1].strip())  # Lê a linha especificada
    else:
        print("Linha não encontrada!")

fim = time.time()
print(f"Tempo de execução (Acesso Direto): {fim - inicio:.6f} segundos")