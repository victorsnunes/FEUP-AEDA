# PADARIA_AEDA-FEUP

This project corresponds to part 1 of the project done in the course **Algoritmos e Estrutura de Dados**, a **2nd year course** in the **Integrated Master's Degree in Informatics and Computing Engineering @ FEUP**

## Project Specification

### Tema 4 – Padaria Baker (Parte 1)
O Sr. António tem uma padaria com muito sucesso na baixa do Porto. Para além de oferecerem pão fresco a
todas as horas do dia, a esposa do Sr. António faz bolos para aniversário a pedido dos clientes. Devido ao
sucesso do negócio, eles querem expandir a sua padaria e por isso mesmo pedem a informatização do seu
sistema de funcionamento completo!
Os clientes utilizam o site para selecionar os produtos que desejam e levantam-nos meia hora depois do
pedido ser feito. Por esta razão, aquando do registo, os clientes são alocados à loja onde lhes é mais
conveniente fazer o levantamento. Sobre os clientes é importante guardar o seu nome, NIF e opinião da
padaria (positiva ou negativa). Ao fazer uma encomenda, o cliente seleciona os produtos e a quantidade que
deseja. Será importante para o cliente saber o preço total do seu pedido. Após ter recebido a encomenda, o
cliente pode atribuir uma avaliação (valor entre 0 e 5) ao serviço prestado pela padaria. A opinião de um
cliente será a média das suas avaliações.
O Sr. António tem dois tipos de clientes: uns em regime normal e outros em regime premium. Os clientes
premium têm a vantagem de acumularem 10 pontos por cada euro de compras feitas na padaria. Quando o
cliente acumula 100 pontos, o cliente premium ganha um desconto de 5% na compra seguinte e os pontos
voltam a zero. Os clientes em regime normal podem também acumular pontos mas só têm direito a um
desconto de 2% quando os seus pontos chegam a 200.
Os produtos oferecidos pelo Sr. António incluem o nome, categoria e preço. Os pães são divididos entre
pequenos e grandes. Na loja do Porto são oferecidos também bolos de 2 camadas. As camadas podem ser
escolhidas dentro de uma lista (crocante, massa folhada, massa de pão de ló).
A padaria inclui vários funcionários que trabalham nas lojas a entregar as encomendas. A empresa guarda o
nome dos trabalhadores, o seu NIF e salário. Quando existe uma encomenda para ser entregue, deve ser
escolhido o funcionário com menos encomendas entregues até ao momento, isto é, a tarefa de entrega de
encomendas deve ser equilibrada entre os funcionários.
O Sr. António quer poder gerir todos os aspetos de funcionamento das padarias. Desta forma, ele quer poder
pesquisar por clientes, funcionários e produtos. Interessa-lhe saber também o volume de vendas (por
quantidade de produto e valor), o número de clientes de cada tipo, e a história do cliente (registo de pontos
e descontos) .
Implemente também outras funcionalidades que considere relevantes, para além dos requisitos globais
enunciados na página inicial.

### Tema 4 – Padaria Baker (Parte 2)
Complemente o sistema já implementado com as seguintes funcionalidades:
Para dinamizar a padaria, o Sr. António decidiu começar a registar o número de encomendas nos quais cada
produto aparece. Esta informação deve ser guardada numa árvore binária de pesquisa, sendo cada produto
ordenado pelo número de encomendas em que consta e, em caso de empate, alfabeticamente pela sua
categoria. Sempre que uma encomenda nova é feita, a contagem de cada produto respetivo deve ser
atualizada. Devem ser permitidas listagens várias, tirando partido da ordenação da árvore.
O Sr. António quer melhorar a opinião dos clientes que fizeram avaliações negativas à padaria. Desta forma,
ele implementou um sistema de entrega de encomendas baseado numa fila de prioridade. Os funcionários
que fazem entregas organizam o seu trajeto com base nesta fila. As prioridades de entrega são definidas
como inversas à avaliação que os clientes fizeram à padaria. Isto é, clientes com pior opinião devem ser os
primeiros a receberem a encomenda. Em caso de empate, são escolhidos os clientes com menor registo de
descontos. Um funcionário tem capacidade de entregar 5 encomendas no máximo. No entanto, o Sr.
António gosta de ter os funcionários todos ocupados e, desta forma, a alocação de encomendas aos
funcionários deve ser gerida equilibradamente entre os mesmos.
A padaria mantém um registo dos funcionários por posto de trabalho numa tabela de dispersão. Quando
um funcionário deixa de trabalhar na padaria, este deve ser eliminado da tabela. Como o ano de 2020 foi
de vendas abundantes e as entregas foram elogiadas pelos clientes, o Sr. António vai aumentar o salário
aos trabalhadores que fazem entregas em 2%. Interessa ainda poder listar ou pesquisar funcionários por
posto.
Implemente outras funcionalidades que considere relevantes, para além dos requisitos globais enunciados.

## Authors

* **João Santos** - [ExSchYte] https://github.com/ExSchYte
* **Victor Nunes** - [victorsnunes] https://github.com/victorsnunes
* **Pedro Pereira** - [pspereira2001] https://github.com/pspereira2001
