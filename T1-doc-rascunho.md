# **FUNDAMENTOS DE REDES DE COMPUTADORES - 2024/2**
## **Trabalho 1: SNTP**
#### Professor: Tiago Alves da Fonseca
#### Grupo: João Pedro Rodrigues Morbeck (202063300), Pedro Henrique da Silva Melo (211039662), Rodrigo de Andrade Lima Orlandi (202017129)

## SISTEMA OPERACIONAL
Ubuntu 22.04.4 LTS (Latest Stable version)

## AMBIENTE DE DESENVOLVIMENTO 
Visual Studio Code 1.96.2

## COMO CONSTRUIR A APLICAÇÃO
1.  Para a compilação do aplicativo em ambiente Linux, foi utilizado o comando Make. O site a seguir o detalha e logo após explica como instalá-lo: [https://wiki.ubuntu.com/ubuntu-make](https://wiki.ubuntu.com/ubuntu-make).

2.  Mova a pasta ‘T1-BUNDA [NOME TEMPORÁRIO]’ para o diretório desejado.

3. Abra o prompt de comando ou ambiente de desenvolvimento que deseja utilizar.

4. Navegue para o diretório em que colocou a pasta e em seguida, até a pasta T1-BUNDA:

```
> cd <nome-do-diretorio>
> cd <T1-BUNDA>
```
5. Por fim, compile o código com a seguinte linha de comando:

```
> make src/main.c
```
## INSTRUÇÕES DE USO

Para executá-lo, a entrada no formado `bin/main <seu-codigo-IP>` deve ser inserida para que possa criar um socket e estabelecer conexão com o servidor STP. Se o código IP não for reconhecido ou a entrada não estiver nos padrões, ele exibirá uma mensagem de erro, representada pela figura 1, a seguir:

### <p style="text-align: center;"><h3>**Figura 1**: Mensagem de erro exibida ao receber argumentos não reconhecidos.</h3></p>
![image1](/img/img1-entrada-errada.png)

1. No terminal, execute o arquivo Main:

```
> bin/main <seu-codigo-ip>
```
2. O socket será criado, e então tentará estabelecer uma conexão com o servidor. A resposta virá em formato de pares de 4 bits, e será traduzida por tabela ASCII para apresentar um resultado com maior legibilidade, como visto na figura 2, a seguir. 

### <p style="text-align: center;"><h3>**Figura 2**: Output esperado do programa.</h3></p>
![image2](/img/img2-saida-esperada.png)

3. Caso o servidor SNTP não responda dentro do período de tempo estabelecido, ocorrerá um *timeout*, e o programa irá retornar que não foi possível a conexão com o servidor, como pode ser observado na figura 3, a seguir:

### <p style="text-align: center;"><h3>**Figura 3**: Exemplo de situação *timeout*.</h3></p>
![image3](/img/img3-timeout.png)

## LIMITAÇÕES CONHECIDAS

O código foi desenvolvido e testado inteiramente com base no sistema operacional Ubuntu.
