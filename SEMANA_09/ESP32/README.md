Exercício Prático sobre Autenticação Multifator

a) (2.0) pontos. Desenvolva uma montagem experimental em protoboard que torne possível a interface do ESP32 com o leitor de impressão digital e com 5 botões (4 botões de dados e 1 botão de confirmação);


b) (2.0) pontos. Desenvolva um código que identifique quando o usuário pressionar cada um dos 4 botões de dados (considere que cada botão é pressionado individualmente) e salve estes dados em um lista com 4 posições (a lista sempre terá a sequência dos últimos 4 botões pressionados);

c) (2.0) pontos. Adicione ao código uma senha pré-cadastrada ("hard-coded", embutida no código) e um procedimento que compare o conteúdo da lista com a senha pré-cadastrada quando o usuário pressionar o botão de confirmação. Quando a comparação retornar verdadeiro, o built-in led do ESP32 deve acender, e ficar apagado em caso contrário. O resultado também deve ser impresso na saída serial;

d) (3.0) (Desenvolva um código que realize a leitura do leitor de impressão digital, compare com uma digital pré-cadastrada. Quando a comparação retornar verdadeiro, o built-in led do ESP32 deve acender, e ficar apagado em caso contrário. O resultado também deve ser impresso na saída serial;

e) (1.0) pontos. Realize a integração dos códigos de leitura de digital e de senha inserida por botões de 
forma que o usuário apresente sua digital, e que após confirmação de que a digital está validada, insira a senha por meio dos 4 botões de dados e pressione confirma para terminar a autenticação. Quando as duas verificações retornarem verdadeiro, o built-in led do ESP32 deve acender, e ficar apagado em caso contrário. O resultado também deve ser impresso na saída serial.