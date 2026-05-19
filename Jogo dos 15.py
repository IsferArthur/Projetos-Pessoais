import random
import os
import time

VERDE = '\033[92m'
VERMELHO = '\033[91m'
RESET = '\033[0m'

def criar_matriz():
    return [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 0]]

def verificar_posicao(matriz, numero):
    for i in range(4):
        for j in range(4):
            if matriz[i][j] == numero:
                return (i, j)
    return None

def mover(matriz, direcao):
    l0, c0 = verificar_posicao(matriz, 0)

    if direcao == 'W':  # Cima
        if l0 > 0:
            matriz[l0][c0] = matriz[l0 - 1][c0]
            l0 -= 1
            matriz[l0][c0] = 0
            return True
    elif direcao == 'S':  # Baixo
        if l0 < 3:
            matriz[l0][c0] = matriz[l0 + 1][c0]
            l0 += 1
            matriz[l0][c0] = 0
            return True
    elif direcao == 'A':  # Esquerda
        if c0 > 0:
            matriz[l0][c0] = matriz[l0][c0 - 1]
            c0 -= 1
            matriz[l0][c0] = 0
            return True
    elif direcao == 'D':  # Direita
        if c0 < 3:
            matriz[l0][c0] = matriz[l0][c0 + 1]
            c0 += 1
            matriz[l0][c0] = 0
            return True

    return False

def imprimir_matriz(matriz, original=None):
    os.system('cls' if os.name == 'nt' else 'clear')

    if original is None:
        original = criar_matriz()

    for i in range(4):
        for j in range(4):
            num = matriz[i][j]
            if num == 0:
                print(f"{'':>4}", end=" ")
            else:
                if original[i][j] == num:
                    print(f"{VERDE}{num:>3}{RESET}", end=" ")
                else:
                    print(f"{VERMELHO}{num:>3}{RESET}", end=" ")
        print()


def embaralhar(matriz, num_jogadas, original=None, rodada=1):
    if original is None:
        original = criar_matriz()

    if rodada == 1:
        os.system('cls' if os.name == 'nt' else 'clear')
        print("Embaralhando com " + str(num_jogadas) + " movimentos...")
        print()
        imprimir_matriz(matriz, original)
        time.sleep(0.5)

    if rodada > num_jogadas:
        print('\033[6;0H')  # Move para linha 6
        print("Pronto para jogar!")
        print()
        return

    # Tenta um movimento válido
    if not mover(matriz, random.choice(['W', 'S', 'A', 'D'])):
        embaralhar(matriz, num_jogadas, original, rodada)
    else:
        # Mostra a animação do movimento
        imprimir_matriz(matriz, original)

        # Delay para visualização
        time.sleep(0.15)

        # Continua a próxima iteração
        embaralhar(matriz, num_jogadas, original, rodada + 1)

def obter_entrada():
    entrada = input("Movimento (W/S/A/D) ou Q: ").upper()
    if entrada in ['W', 'S', 'A', 'D', 'Q']:
        return entrada
    print("Inválido!")
    return obter_entrada()

def jogar():
    os.system('cls' if os.name == 'nt' else 'clear')
    print("=" * 30)
    print("JOGO DOS 15")
    print("=" * 30)
    print("\nDificuldade:")
    print("1 - Principiante (50)")
    print("2 - Intermediário (100)")
    print("3 - Especialista (200)\n")

    opcoes = {'1': 10, '2': 100, '3': 200}
    while True:
        opcao = input("Escolha: ")
        if opcao in opcoes:
            num_jogadas = opcoes[opcao]
            break
        print("Inválido!")

    matriz = criar_matriz()
    original = criar_matriz()
    embaralhar(matriz, num_jogadas, original)

    rodadas = 0

    while True:
        imprimir_matriz(matriz, original)
        print(f"Movimentos: {rodadas}\n")

        entrada = obter_entrada()

        if entrada == 'Q':
            os.system('cls' if os.name == 'nt' else 'clear')
            print("Até logo!")
            break

        if mover(matriz, entrada):
            rodadas += 1
        else:
            imprimir_matriz(matriz, original)
            print(f"Movimentos: {rodadas}")
            print("Inválido!\n")
            input("Pressione ENTER para continuar...")
            continue

        if matriz == original:
            imprimir_matriz(matriz, original)
            print(f"Movimentos: {rodadas}")
            print(f"\n{'=' * 30}")
            print(f"VENCEU com {rodadas} movimentos!")
            print("=" * 30)

            while True:
                resp = input("\nJogar novamente? (S/N): ").upper()
                if resp == 'S':
                    jogar()
                    return
                elif resp == 'N':
                    os.system('cls' if os.name == 'nt' else 'clear')
                    print("Obrigado!")
                    return
if __name__ == "__main__":
    jogar()