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

<div id="equipamentos"> 
<h2> Descrição dos Equipamentos e Software Utilizados</h2>
<div align="justify"> 

Nesta seção, são apresentados os equipamentos e software utilizados durante o desenvolvimento do projeto.

<h3> O kit de desenvolvimento DE1-SoC</h3>

A placa DE1-SoC é um kit de desenvolvimento que integra um processador ARM Cortex-A9 dual-core com um FPGA Cyclone V da Intel. Este dispositivo oferece uma variedade de periféricos, como display de 7 segmentos, porta Ethernet, USB, porta de áudio, entre outros, tornando-o adequado para projetos que exigem integração de software e hardware. É comumente empregado em ambientes educacionais e de pesquisa para o estudo e desenvolvimento em sistemas embarcados e FPGA

<p align="center">
  <img src="Images/DE1-SoC_top45_01.jpg" width = "400" />
</p>
<p align="center"><strong>Kit de desenvolvimento DE1-SoC</strong></p>

<h3> Mouse</h3>

PRECISA ATUALIZAR.

<p align="center">
  <img src="Images/Monitor.jpg" width = "400" />
</p>
<p align="center"><strong>Monitor CRT DELL</strong></p>

<h3> Linguagem C</h3>

A seleção da linguagem C foi motivada por sua eficiência, portabilidade e ampla adoção em sistemas embarcados. Sua sintaxe direta proporciona um controle preciso sobre o hardware, ao passo que suas bibliotecas padrão e ferramentas simplificam o desenvolvimento de código compacto e otimizado para dispositivos com recursos limitados.

<h3> Compilador GNU</h3>

O GCC, que significa "GNU Compiler Collection" (Coleção de Compiladores GNU), é uma distribuição integrada de compiladores amplamente adotada que suporta diversas linguagens de programação, como C, C++, Objective-C, Fortran, Ada, entre outras. Ao ser executado, o GCC atravessa etapas de pré-processamento, compilação, montagem e ligação. Ele disponibiliza uma vasta variedade de opções de linha de comando para personalização, o que simplifica a configuração de acordo com as necessidades específicas do desenvolvedor.

<h3>Vscode</h3>

O Visual Studio Code, também conhecido como VSCode, é um ambiente de desenvolvimento muito popular. Desenvolvido pela Microsoft, é um editor de código aberto e gratuito que oferece recursos como realce de sintaxe, conclusão automática de código e depuração integrada. Ele suporta uma variedade de linguagens de programação e possui um sistema de extensões que permite personalizar e estender suas funcionalidades. No projeto, o VSCode foi utilizado para desenvolver o código-fonte do jogo e formatar o README.

</div>
</div>

<div id="arq_CPU"> 
<h2> Arquitetura da placa DE1-SoC</h2>
<div align="justify">

Nesta seção, será explorado a arquitetura da placa DE1-SoC, incluindo o processador ARM Cortex-A9, a estrutura de registros, o mapeamento de dispositivos de entrada/saída na memória, a memória utilizada, a comunicação entre o processador e o FPGA, e o processo de compilação nativa na placa.

<h3>Visão Geral dos Recursos do Processador ARM Cortex-A9 </h3>

O processador ARM Cortex-A9 utiliza uma arquitetura de conjunto de instruções reduzido (RISC), com operações aritméticas e lógicas realizadas nos seus registradores de uso geral. O movimento de dados entre a memória e os registradores é feito por instruções Load e Store, utilizando uma palavra de 32 bits e endereçamento de bytes no formato little-endian.

<h3>Estrutura do Registro</h3>

O processador ARM Cortex-A9 possui 15 registros de uso geral (R0 a R14), um contador de programa (R15) e um registro de status de programa atual, CPSR, todos com 32 bits. Dois registros são tratados de maneira especial: R13 é o Stack Pointer e R14 é um registro de link na ligação de sub-rotina.

<p align="center">
  <img src="Images/reg.png" width = "600" />
</p>
<p align="center"><strong>Registradores disponíveis e sua organização interna</strong></p>

<h3>Instruções e Conjunto Thumb</h3>

As instruções têm 32 bits e são armazenadas na memória alinhadas em palavras. O conjunto Thumb oferece uma versão compacta com instruções de 16 bits, reduzindo os requisitos de memória, o que é vantajoso em aplicações embarcadas.

<h3>Memória</h3>

O HPS inclui uma interface de memória que conecta o ARM MPCORE a uma memória DDR3 de 1 GB. Essa memória é comumente utilizada para armazenamento de programas e dados pelos processadores ARM. A memória é organizada em 256M x 32 bits e pode ser acessada por operações de palavra (32 bits), meia-palavra e byte.

<h3>Mapeamento de Dispositivos de E/S</h3>

Os dispositivos de entrada/saída acessíveis pelo processador ARM são mapeados na memória e podem ser acessados como locais de memória através de instruções Load e Store.

<h3>Interrupções de Hardware</h3>

As interrupções de hardware podem ser geradas por dispositivos de E/S, ativando as entradas de solicitação de interrupção do processador (IRQ ou FIQ). Quando ocorre uma interrupção, o processador entra no modo de exceção correspondente e salva o estado atual do programa. O endereço salvo no registrador de link deve ser decrementado em 4 antes de retornar ao programa interrompido.

<h3>Diagrama de Blocos do Sistema DE1-SoC</h3>

O sistema DE1-SoC é composto pelo Hard Processor System (HPS) e FPGA dentro do chip Cyclone V SoC. O HPS inclui um processador dual-core ARM Cortex-A9, uma porta de memória DDR3 e dispositivos periféricos. O FPGA implementa dois processadores Intel Nios II e diversas portas periféricas.


<p align="center">
  <img src="Images/Diagrama-em-blocos.png" width = "600" />
</p>
<p align="center"><strong>Diagrama da arquitetura da placa DE1-SoC</strong></p>


<h3>Comunicação entre Processador e FPGA via JTAG</h3>

A porta JTAG possibilita a comunicação entre a placa DE1-SoC e o computador host, permitindo a transferência de arquivos de programação FPGA para a placa DE1-SoC e o monitoramento através do programa Intel FPGA Monitor.

<h3>Compilação Nativa na Placa DE1-SoC</h3>

A compilação nativa ocorre quando um programa é compilado em um sistema para rodar na mesma arquitetura do próprio sistema. Neste caso, a compilação nativa de programas pode ser realizada na placa DE1-SoC através da linha de comando do Linux, utilizando sua cadeia de ferramentas de compilação integrada. O comando gcc invoca o GNU C Compiler, um compilador de código aberto amplamente utilizado para compilar programas Linux, já citado anteriormente.

</div>
</div>

<div id="Perifericos-utilizados"> 
<h2> Periféricos da Placa DE1-SoC Utilizados </h2>
<div align="justify">

A seguir, será feita as descrições gerais dos periféricos utilizados da placa DE1-SoC e seus aspectos mais importantes. A Figura abaixo mostra a placa FPGA, com as indicações dos seus dispositivos que serão citados.

<p align="center">
  <img src="Images/BoardLayout.png" width = "600" />
</p>
<p align="center"><strong> Layout dos periféricos da placa</strong></p>

<h3>Gigabit Ethernet</h3>

A placa suporta transferência Gigabit Ethernet por um chip externo Micrel KSZ9021RN PHY e função HPS Ethernet MAC. 

Existem dois LEDs, LED verde (LEDG) e LED amarelo (LEDY), que representam o status da Ethernet PHY (KSZ9021RNI). Os sinais de controle dos LEDs são conectados aos LEDs no conector RJ45. A conexão da placa ao Gigabit Ethernet é estabelecida quando o LEDG acende.

<h3>USB Host</h3>

A placa possui duas portas USB 2.0 tipo-A com um controlador SMSC USB3300 e um controlador de hub de 2 portas. 

O dispositivo SMSC USB3300 de 32 pinos faz interface com o controlador de hub SMSC USB2512B, hub este que permite expandir o número de portas USB disponíveis na placa, permitindo que mais dispositivos USB sejam conectados. Este dispositivo suporta UTMI+ Low Pin Interface (ULPI), que se comunica com o controlador USB 2.0 em HPS. 

O PHY, responsável por lidar com a camada física da comunicação USB, incluindo a modulação/demodulação de sinais elétricos, opera no modo Host conectando o pino ID do USB3300 ao terra. Ao operar no modo Host, o dispositivo é alimentado pelas duas portas USB tipo A.


<h3>Botões</h3>

A placa disponibiliza quatro botões para utilização. Os dados de leitura dos botões são armazenados em um registrador de dados, com seus quatro bits menos significativos representando cada um dos botões. Quando um botão é pressionado, o seu respectivo bit é setado para 1, e quando é solto, para 0.

Existem outros dois registradores, o "interruptmask" e o "edgecapture". Esses registradores possuem um bit para cada botão, como o registrador de dados, porém, com funções diferentes. O "interruptmask" pode habilitar interrupções para cada botão, setando o seu respectivo bit para 1. O "edgecapture" seta o bit para 1 quando o botão é pressionado, e permanece nesse valor até que seja zerado diretamente. Setar um bit do "edgecapture" para 0 pode ser feito escrevendo o valor 1.

</div>

<div id="Drives"> 
<h2> Drives de Dispositivos de Entrada e Saída (E/S)</h2>
<div align="justify">

Para interagir com os dispositivos periféricos de hardware, é necessário empregar drivers de software. Esses drivers são programas que fornecem a interface necessária para enviar comandos e receber dados desses dispositivos. Os drivers utilizados são conhecidos como módulos de kernel, os quais podem ser carregados dinamicamente no núcleo do sistema operacional durante a execução do programa.

A distribuição de Linux do DE1-SoC-UP disponibiliza módulos de kernel prontos para realizar essa comunicação. Na linguagem C, esses módulos podem ser acessados adicionando na compilação do programa o comando "-lintelfpgaup", e no código, a declaração "#include <intelfpgaup/xxx.h>", sendo "xxx", o nome do driver utilizado. A seguir, serão descritas as funções pertinentes do módulo de kernel utilizado.

<h3> Botões </h3>

Módulo indicado pelo nome "KEYS". As funções utilizadas são:

* KEY_open: Abre a comunicação do dispositivo dos botões;
* KEY_read: Lê os dados dos botões. É passado como parâmetro um ponteiro que irá setar os sinais retornados dos botões no endereço indicado (0-Não pressionado e 1-Pressionado). Se todos os botões não estão pressionados, o retorno é 0b0000. Caso todos estejam pressionados, o retorno é 0b1111.
* KEY_close: Fecha a comunicação do dispositivo dos botões;

</div>

<div id="testes"> 
<h2> Testes </h2>
<div align="justify">

A seguir, a descrição dos testes realizados para garantir o adequado funcionamento do sistema.

* Transição da tela inicial para a partida.

<p align="center">
  <img src="Gifs/TelaInicial_Partida.gif" width = "400" />
</p>
<p align="center"><strong>Transição da tela inicial para a partida</strong></p>

* Jogador tenta escolher quadrante já ocupado.

<p align="center">
  <img src="Gifs/QuadranteOcupado.gif" width = "400" />
</p>
<p align="center"><strong>Quadrante já ocupado</strong></p>

* Jogador X ganha e escolhe jogar novamente.

<p align="center">
  <img src="Gifs/JogadorX_Ganha.gif" width = "400" />
</p>
<p align="center"><strong>Jogador X ganha</strong></p>

* Jogador O ganha e escolhe jogar novamente.

<p align="center">
  <img src="Gifs/JogadorO_Ganha.gif" width = "400" />
</p>
<p align="center"><strong>Jogador O ganha</strong></p>

* Partida empata e escolhe jogar novamente.

<p align="center">
  <img src="Gifs/Empate.gif" width = "400" />
</p>
<p align="center"><strong>Partida empata</strong></p>

* Um jogador ganha e escolhe sair do jogo.

<p align="center">
  <img src="Gifs/SairJogo.gif" width = "400" />
</p>
<p align="center"><strong>Saindo do jogo</strong></p>

<div id="conclusao"> 
<h2> Conclusão </h2>
<div align="justify">

O desenvolvimento do clássico Jogo da Velha, por meio do código em linguagem C no kit de desenvolvimento DE1-SoC, provou proporcionar uma experiência de usuário interativa, simples e direta. Durante o processo de implementação, todos os requisitos estabelecidos foram devidamente atendidos, utilizando da arquitetura da placa e seus drivers como base sólida para a concepção do jogo e desenvolvimento dos algoritmos necessários.

A integração fluida entre o software e o hardware, possibilitada pela placa, permitiu a utilização integrada dos periféricos botões e USB Host (para captura dos movimentos do mouse), amplificando assim, a imersão durante a jogabilidade. Os testes realizados comprovaram a eficiência e credibilidade do sistema, confirmando sua capacidade de operar de maneira consistente em várias condições de jogo.

Este projeto, além de cumprir com seus objetivos iniciais, permitiu uma ampliação significativa dos conhecimentos em sistemas embarcados e arquitetura ARM, além de capacitar os desenvolvedores a integrar aspectos tanto de software quanto de hardware, firmando uma base sólida para futuras explorações nas áreas de sistemas digitais e desenvolvimento de software.

</div>
</div>

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