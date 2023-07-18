import requests
import random

# Função para embaralhar as palavras de uma lista
def shuffle_words(word_list):
    shuffled_words = list(word_list)
    random.shuffle(shuffled_words)
    return shuffled_words

# URL do arquivo de texto com as palavras
url = 'https://www.ime.usp.br/~pf/dicios/br-sem-acentos.txt'  # Substitua pela URL do arquivo de texto

try:
    # Faz a solicitação HTTP para o arquivo de texto
    response = requests.get(url)
    # Verifica se a solicitação foi bem-sucedida
    if response.status_code == 200:
        # Obtém o conteúdo do arquivo de texto
        words_text = response.text
        # Divide o texto em linhas para obter as palavras
        words = words_text.strip().split()
        # Embaralha as palavras
        shuffled_words = shuffle_words(words)
        # Salva as palavras embaralhadas em um arquivo .txt
        with open('palavras_embaralhadas.txt', 'w', encoding='utf-8') as file:
            for word in shuffled_words:
                file.write(word + '\n')
        print("As palavras foram embaralhadas e salvas em 'palavras_embaralhadas.txt'.")
    else:
        print("Não foi possível acessar o arquivo de texto. Verifique a URL e tente novamente.")
except requests.exceptions.RequestException as e:
    print("Ocorreu um erro ao fazer a solicitação HTTP:", e)
except Exception as ex:
    print("Ocorreu um erro:", ex)
