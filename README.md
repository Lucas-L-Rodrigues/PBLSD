<h1 align="center"> Jogo da Velha</h1>
<h3 align="center"> O clássico Jogo da Velha, agora desenvolvido para o kit de desenvolvimento DE1-SoC utilizando linguagem C </h3>

<div align="justify"> 
<div id="especificacoes-do-projeto"> 
<h2> Especificações do Projeto</h2>

O mercado de jogos movimenta bilhões anualmente, e continua sendo uma força altamente impulsionadora da economia global. Cada vez mais é observada uma alta demanda por experiências imersirvas e inovadoras, que buscam cativar o público com um alto nível de tecnologia, entretanto, ainda é possível observar uma demanda pelos jogos clássicos.

Neste cenário, o clássico jogo da velha surge como um exemplo que resistiu ao tempo e continua marcando gerações. O presente projeto tem como intuito desenvolver um console que implemente uma clássica versão do atemporal jogo da velha, onde o mesmo, deve ser executado em uma interface em modo texto utilizando os recursos da placa de desenvolvimento DE1-SOC.

Os requisitos para elaboração do projeto estão descritos a seguir:

* O jogo deve permitir a interação de dois jogadores, de forma que a escolha da posição de marcação no tabuleiro em cada jogada (assim como a confirmação da jogada) deva ser captada por um mouse conectado a uma das portas USB existentes no Kit de desenvolvimento DE1-SoC.

*  O código deve ser escrito em linguagem C
*  O sistema só poderá utilizar os componentes disponíveis na placa.

O controle do jogo (iniciar, pausar, resetar, etc...), pode ser feito a partir dos botões e chaves da placa, o display de 7 segmentos e os leds também podem ser utilizados para exibição de qualquer informação, se necessário.

</div>

<h2>  Equipe: <br></h2>
<uL> 
  <li><a href="https://github.com/LucaasGy">Lucas Gabriel Cerqueira Santos Lima</a></li>
  <li><a href="https://github.com/Lucas-L-Rodrigues">Lucas Lima Rodrigues</a></li>
  <li><a href="https://github.com/felipe-py">Luis Felipe Cunha Silva</a></li>
</ul>

<div id="execucaoProjeto"> 
<h2> Execução do Projeto  </h2>
<div align="justify">

Para iniciar o jogo, é necessário seguir os seguintes passos para obter o código-fonte, compilar o código em C e executá-lo em um dispositivo FPGA DE1-SoC. 

**Passo 1: Clonar o Repositório**

Abra o terminal e execute o seguinte comando para obter o código do repositório:

    git clone https://github.com/Lucas-L-Rodrigues/PBLSD.git

**Passo 2: Compilar o Código em C**

Compile e execute o código usando o comando:

    make

    make run

Para apagar arquivos gerados na compilação, use o comando:

    make clearGerados

Para apagar todos os arquivos, com exceção do Makefile, use o comando:

    make clearAll