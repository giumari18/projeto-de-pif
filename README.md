## 🍳 Lógica à La Carte

> Projeto desenvolvido para a disciplina: **Programação Imperativa e Funcional - 2025.2**

### 🧑‍💻 Equipe

* Aguinaldo Neto (@netokemon)
* Caliel Feijó (@poeisie)
* Elis Tenório (@elistenorio)
* Eulália Albuquerque (@eulalialbuquerque)
* Giulia Ferreira (@giumari18)
* Sarah Cyrne (@sarahcyrne) 

## 📖 Descrição do Jogo

Diego, ex-professor de tecnologia e agora chef em crise existencial, largou tudo para seguir sua paixão pela gastronomia.
Mas há um detalhe: ele organizou seu livro de receitas como se fosse um tratado de lógica proposicional.
Cada ingrediente depende de premissas, implicações, conjunções e negações.

Na cozinha de Diego, não basta saber cortar cebola — é preciso provar logicamente que ela deveria estar no prato.

E é aqui que você entra:
Você é o assistente responsável por transformar o caos da cozinha em ordem lógica gourmet. Somente resolvendo os desafios lógicos você conseguirá liberar os ingredientes e salvar o jantar.

## 🎯 Objetivo do Jogo

Desbloquear ingredientes interpretando premissas lógico-matemáticas — e montar o prato perfeito!

Para finalizar cada receita, você deve deduzir:

✔ quais ingredientes realmente pertencem ao prato

✔ quais premissas são verdadeiras

✔ qual composição final faz sentido dentro das regras impostas

Cada receita funciona como um puzzle culinário-lógico, com dificuldade crescente, novos ingredientes e relações cada vez mais complexas.

## 🍲 Como Jogar

### 🧾 Sistema de Receitas

Cada receita apresenta:

- Lista de ingredientes

- Arte ASCII temática

- Nível de dificuldade

- Premissas que controlam o uso de cada ingrediente

Seu trabalho é interpretar essas regras e decidir o que pode ou não pode entrar na panela.
Errou uma premissa?
O prato pode sair… estranho. 😬

## 🔍 Premissas e Dedução

Ao iniciar uma receita, você verá afirmações como:

“Se houver alho, não pode haver cebola.”

“Tomate só entra no prato se as premissas 1 e 3 forem verdadeiras.”

“Ou manjericão ou orégano — mas nunca os dois.”

Aqui começa o raciocínio lógico: cada premissa funciona como um conectivo (E, OU, SE-ENTÃO, NÃO) que define a validade de um ingrediente.

Seu papel é marcar cada premissa como verdadeira ou falsa e deduzir:

👉 Qual ingrediente está liberado
👉 Qual ingrediente deve ser bloqueado
👉 Qual combinação respeita todas as regras

## 🥕 Liberação dos Ingredientes

Com base nas suas respostas:

- Ingredientes corretos são liberados para Diego
- Ingredientes incorretos são descartados
- Ingredientes mal deduzidos entram na receita e… bagunçam tudo
- A combinação final depende 100% da sua lógica

Cada decisão muda o resultado final. Não existe chute: existe inferência.

## 🍽️ Preparação e Avaliação

Depois que você resolve as premissas, Diego monta o prato baseado nas suas escolhas.

A avaliação final usa um sistema de 1 a 5 estrelas, considerando:

1. sua precisão lógica
2. sua capacidade de completar a receita
3. sua eficiência nas tentativas

Quanto mais bem montado o prato, mais estrelas (e elogios culinários/lógicos) você recebe.
E, claro, isso gera XP para subir de nível.

## 📈 Progresso

Acumule XP, avance na hierarquia da cozinha e desbloqueie desafios cada vez mais elaborados.

✨ Comece como Aprendiz

🍳 Evolua para Commis

🥘 Chegue a Sous Chef

🏅 Torne-se Chef Executivo

👑 E conquiste a glória máxima: Master Chef Executivo

Cada nível libera novas receitas, premissas mais complexas, conectivos mais traiçoeiros e ingredientes mais difíceis de deduzir.

⚡ Mais rápido

🎯 Mais preciso

🧠 Mais lógico

👨‍🍳 Mais chef

---


## 🎮 Como rodar o jogo


Para executar o jogo localmente, siga os passos abaixo:


### ⬇️ 1. Baixando dependências


- Para rodar, você precisa ter o gcc:


**Ubuntu**
```bash
sudo apt update
sudo apt install build-essential
```


**Fedora**
```bash
sudo dnf install gcc gcc-c++
```


**Arch / Manjaro**
```bash
sudo pacman -S gcc
```




### 📥 2. Clonar o repositório


```bash
git clone https://github.com/giumari18/projeto-de-pif.git
cd projeto-de-pif
```


### 🔨 3. Compilar o projeto utilizando o Makefile


```bash
make
```


### ▶️ 4. Executar o jogo após a compilação


```bash
./build/cli_exec
```




