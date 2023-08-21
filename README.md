# Automação Residencial - Projeto de Conclusão Curso técnico em Mecatrônica

Trabalho de conclusão de curso usando aplicativo para controlar uma maquete de uma residência através do bluetooth

## Projeto de conclusão de Curso Técnico em Mecatrônica, Escola Etecsal 2019

### Escopo

O projeto conta com um aplicativo criado no site MIT app inventor 2 para controlar uma maquete de uma residência, no hardware foi utilizado 2 arduinos e uma comunicação serial entre eles, mais um modulo bluetooth *HC-05* e um modulo *RFID RC522*

### Desafio

  - Nosso maior desafio técnico foi estabelecer uma comunicação confiável e eficaz entre os dispositivos, optamos pela arquitetura onde havia um Arduino Mestre e um escravo, concentramos os dispositivos de entrada no Arduino mestre e os de saída no escravo dessa foram focamos em na comuncação e performace apenas do Arduino Meste. Entre os dois arduino a comunicação foi utilizada comunicação Serial e entre o Mestre é o aplicativo utilizamos bluetooth, acima da camada fisica criamos um protocolo de comunicação comum entre todos os dispositivos para a troca de comunicação.

  - Como equipe o nosso maior desafio foi atender os os prazos e a entrega de todos os regursos funcionando. Nossa equipe era formada em sua maioria por pessoas que trabalhavam durante o dia oq nos limitou apenas aos horarios de aula para a executação, logo foi indispensável uma gestão eficaz do projeto. Utilizamos uma adptação de metodologia agéis baseado na leitura do livro  **Scrum: A arte de fazer o dobro do trabalho na metade do tempo** e conseguimos entregar o projeto concluido e com nota máxima.


Video de Apresentação: [Projeto Casa inteligente](https://youtu.be/JxLmuOUkab8)

### Aplicativo criado no APP INVENTOR 2

Projeto: [Aplicativo controle casa automatizada](https://gallery.appinventor.mit.edu/?galleryid=5268691490570240)

![app casaintel 1](https://github.com/LeandroFogaca/aplicativo-bluetooth-arduino/assets/27831619/82d27dcf-bc04-4ed5-b581-09a3bddbdde5)
