# Nome dos integrantes
João Augusto Zanardo de Lima - 11201920195

Guilherme Klinkerfuss Guimarães Pereira - 11201912414

# Explicação do Projeto

O projeto consiste em uma espiral a partir de pontos desenhados na tela, aonde o usuário pode interagir com a aplicação de algumas formas, sendo elas:
 - selecionar o número de pontos que ele gostaria (para valores negativos o sentido da espiral será invertido)
 - definir a escala o que impacta no tamanho em que a espiral será printada na tela
 - definir a angulação da espiral
 - pode limpar a tela
 - resetar as configurações para os valores iniciais
 - gerar uma nova espiral

# Implementação do Projeto
Configuração Inicial:

1 - Configuração
  * A aplicação utiliza o framework ABCg para criar e gerenciar a janela gráfica.
  * O programa começa configurando os shaders do OpenGL, que definem como os vértices e fragmentos são processados. O vertex shader simplesmente define o tamanho e a posição dos pontos, enquanto o fragment shader define a cor (neste caso, sempre branco).

2 - Criação da Janela (tela):
 * No método onCreate(), a janela é configurada com uma cor de fundo preta (R=0, G=0, B=0, A=1) usando abcg::glClearColor, e o fundo é limpo com abcg::glClear para garantir que a janela esteja limpa no início.

3 - Renderização dos Pontos:
 * A função generateSpiral é chamada no onCreate() para gerar os pontos da espiral. Esses pontos são armazenados em um vetor chamado m_Points. Cada ponto é definido por suas coordenadas x e y.
 * No método onPaint(), os pontos são desenhados na tela. Ele começa verificando se todos os pontos foram desenhados (controlado pela variável m_Index). Se não, ele desenha um ponto por vez, incrementando m_Index a cada quadro até que todos os pontos tenham sido 
   desenhados.

4 - Interface Gráfica do Usuário (GUI):
 * O método onPaintUI é usado para criar uma interface gráfica do usuário (GUI) com o framework ImGui. A GUI permite ao usuário interagir com a aplicação.
 * Ela inclui botões para "Limpar a janela", alterar o número de pontos, escala e ângulo, bem como botões para "Reset" (redefinir os valores padrão) e "Gerar Espiral" (gerar a espiral com base nas configurações atuais).
 * Se o número de pontos for negativo, a aplicação gera uma espiral reversa invertendo o ângulo.

5 - Geração da Espiral:
 * generateSpiral() e generateReverseSpiral() são funções para gerar os pontos da espiral com base nas configurações atuais, como o número de pontos, escala e ângulo. Uma delas é chamada quando o usuário clica no botão "Gerar Espiral" com base no sinal do número de pontos.
 * generateSpiral() gera uma espiral padrão, enquanto generateReverseSpiral() gera uma espiral reversa.


## Para ver o resultado final abre no navegador:
## https://jozanardo.github.io/Aplicacao-interativa-com-graficos-2D/
