# Trabalho Final da disciplina de Tópicos Especiais III 

## Projeto Smart Lamp

#### Dispositivos embarcados
- Hardware necessário
    - Arduino UNO
    - Shield Ethernet
    - Sensor de Luminosidade
    - LED'S
    - Resistores
    - Jumpers
- Circuito
![Arduino](arduinoproto.jpeg)
- Funcionamento

Basicamente, precisa definir variáveis com ip que o arduino vai usar, ip do servidor (máquina que vai estar rodando o serviço consumido pelo arduino), uma variável para guardar o pino que o LED está ligado, uma variável para ficar armazenando o valor gerado pelo sensor de luminosidade, e as referências para o Shield Ethernet e o cliente do MQTT. No código você vai iniciar uma nova conexão com a internet, se conectar ao servidor, subscrever em um tópico/serviço do servidor e setar um método que deverá ser chamado sempre que alguma alteração for feita no tópico ou serviço subscrito.

**Método Callback** - Principal método da aplicação, pois é ele que contém a lógica de negócio do sistema. Este método recebe como parâmetro um tópico e uma mensagem. No caso deste sistema eu verifico se a mensagem é exatamente "ligar" ou "desligar", caso passem no teste ele liga ou desliga a lâmpada, neste caso representado como LED.

**Método Reconect**
Método auxiliar, responsável por reconectar o arduino ao servidor, caso por algum motivo se desconecte. Caso consiga se conectar ele subscreve nos tópicos novamente. Caso não consiga ele fica tentando reconectar novamente a cada 5 segundos.

**Método Loop**
Responsável por verificar se o arduino está conectado, caso não esteja chama o método Reconect indefinidamente até conseguir conexão. Este método também é responsável por ficar lendo o valor na porta analógica do sensor de luminosidade, este valor é publicado em um topico ou serviço no servidor. Esta operação de ler e publicar valor lido do sensor é realizado a cada 1 segundo(Pode variam conforme a sua vontade).

#### Protocolo de comunicação e controle
#### Serviços na internet
