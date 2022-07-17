## ===============================================================

## SSC0902 – Prof. Fernando Osório - ICMC 202 1 - 2

## TRABALHO PRÁTICO FINAL – Programação MIPS (MARS/SPIM Simulador)

## ===============================================================

# OPÇÃO 02 PROC-IMAGE : Descrição do Trab. Prático TF - MIPS

Atenção: o processamento de imagens pode ser

implementado usando o MARS (preferencial) ou SPIM

## Executar os seguintes passos:

( 1 ) Ler o arquivo do disco “imagem.pgm” (procure colocar este arquivo no mesmo diretório do
executável do simulador), contendo uma imagem. Exemplos de arquivos serão disponibilizados pelo
professor. Esta imagem está em um formato chamado, PGM salvo em modo binário (tipo P5), mas não
se preocupe, basta ler do disco um total de 100x100 (10.000 pixels, 1 byte por pixel em tons de cinza)
+ 38 bytes cabeçalho da imagem => Total 10.038 bytes a serem lidos.

A imagem começa em +38 bytes do início do arquivo (depois do 4º byte com valor 0Ah)
Este arquivo deve ser lido para a memória usando as funções do sistema operacional “SysCalls”.

(2) Gerar o histograma de cores, no caso, por ser uma imagem com “tons de cinza”, gerar o histograma
com a contagem do número de ocorrências de cada um dos tons de cinza. A imagem tem um conjunto
de 10.000 pixels, onde cada píxel tem um tom de cor, um valor da intensidade que varia de Zero (preto)
até 2 55 (branco), gerando os 256 “tons de cinza”. O histograma conta quantas vezes cada valor (entre 0
e 2 55 ) ocorre na imagem, gerando um vetor de 256 valores onde cada valor representa a contagem de
ocorrências daquele tom na imagem.

(3) Exibir na tela os valores do histograma, na seguinte forma:

<nro. da intensidade> - <nro. de ocorrências>
Será exibida na tela uma lista de 256 pares de valores intensidade/ocorrência. Por exemplo:
( 0 : 50 ) ( 1 : 23) ( 2 : 290 ) ... ( 255 : 1321 )

Neste exemplo, o valor de tonalidade 0 ocorre 50 vezes, e o valor 255 ocorre 1 321 vezes dentro dos
1 0.000 pixels da imagem.


( 4 ) Solicitar para o usuário que digite um limiar (threshold) que será usado para binarizar a imagem, ou
seja, transformar a imagem em uma imagem contendo apenas pixels pretos e brancos. Os pixels que
possuem um valor abaixo do threshold/limiar devem ser convertidos para Zero (valor 0 = preto) e os
pixels com valores maiores ou iguais ao threshold/limiar devem ser convertidos para 255 (valor 255 =
branco).

(5) Salvar em disco a noma imagem com o nome “imgproc.pgm”, usando exatamente os mesmos 38
bytes do cabeçalho no início da imagem, seguido pela nova imagem gerada pelo processo de binarização
descrito no passo anterior (4). Portanto, você deve copiar os MESMOS 38 bytes iniciais do arquivo
original lido, seguido dos 10.000 novos bytes resultantes da operação de binarização realizada.

OBSERVAÇÕES e DICAS IMPORTANTES:

- Os arquivo de imagens com extensão “.pgm” podem ser abertos diretamente usando o IrfanView
    para Windows (https://www.irfanview.com/) ou o software ImageJ que roda em Java –
    Win/Linux (http://imagej.nih.gov/ij)
- Você pode “olhar dentro” do conteúdo do arquivo de imagem neste site: https://hexed.it/
- Sobre o formato PGM: [http://paulbourke.net/dataformats/ppm/](http://paulbourke.net/dataformats/ppm/)
    [http://netpbm.sourceforge.net/doc/pgm.html](http://netpbm.sourceforge.net/doc/pgm.html)
- Considere o Formato P 5 , ou seja, imagens em tons de cinza, com 1 byte por pixel (nível de
    intensidade – tons de cinza), e em binário. Veja o exemplo de uma imagem PGM no link
    acima. O formato PGM P5 é igual ao formato PGM P2, porém no P2 os valores estão escritos
    no arquivo em formato texto, ou seja, com caracteres ASCII.
- As imagens PGM podem ter diferentes resoluções e níveis de quantização (quantidade de
    tons) diferentes, mas no trabalho vamos considerar o formato PGM tipo P 5 com 25 6 tons
    (valores dos pixels de 0 a 255) e sempre com uma resolução de 100 x 100 pixels. Exemplos de
    arquivos binários PGM contendo imagens 100 x100 serão fornecidos pelo professor.
