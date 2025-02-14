import time

# Início da medição de tempo
inicio = time.time()

# Abre o arquivo e lê linha por linha
with open('dados.txt', 'r') as arquivo:
    for linha in arquivo:
        print(linha.strip())  # Remove espaços em branco e imprime a linha

# Fim da medição de tempo
fim = time.time()
print(f"Tempo de execução (Acesso Sequencial): {fim - inicio:.6f} segundos")