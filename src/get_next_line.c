/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:57:48 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/30 18:45:25 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// essa função lê um BUFFER_SIZE, armazena no store_rest, e confere se esse bloco lido (BUFFER_SIZE), tem uma
// quebra de linha, se não tiver, lê mais um bloco, armazena no fim do store_rest e procura a quebra de linha
// assim, chama repetidamente a função read até que uma quebra de linha seja encontrada, ou acabe o texto para ler
static char	*read_buffers(int fd, char *store_rest, char *buffer) // recebemos o fd do arquivo, o resto do buffer,
// e o buffer
{
	int		read_bytes; // criamos um inteiro que irá receber o número de bytes lidos pela função read
	char	*temp_to_join; // criamos um ponteiro para string que receberá temporariamente o store_rest

	read_bytes = 1; // iniciamos em 1, na verdade serve qualquer valor maior que zero
	while (1) // fazemos um while sempre verdadeiro, pois queremos que ele pare apenas se sair em
	// algum return ou break, isso nos dá certexa de que algum dos objetivos foi atingido
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE); // armazenamos no read_bytes o número de bytes lidos
		// pela função read. A função read lê o arquivo numerado pelo fd, ela lê de x bytes em x bytes, e
		// essa quantidade de bytes é passada pelo BUFFER_SIZE, e por fim, esses x bytes lidos são 
		// armazenados na string buffer
		if (read_bytes == -1) // se read_bytes for -1, deu-se um erro na leitura
			return (NULL); // então retornamos NULL
		else if (read_bytes == 0) // se read_bytes for 0, ou o arquivo a ser lido estpa vazio, ou já
		// acabamos de ler, então...
			break ; // paramos esse while, ou saímos desse loop;
		buffer[read_bytes] = '\0'; // caso tenha ocorrido tudo certo com a leitura, a posição final da string recebe
		// o byte nulo
		if (!store_rest) // se o armazenamento do buffer, o store_rest, estiver vazio
			store_rest = ft_strdup(""); // ele recebe o malloc de uma string vazia, dada pela função ft_strdup
		temp_to_join = store_rest; // temp_to_join recebe bem temporariamente o store_rest
		store_buffer = ft_strjoin(temp_to_join, buffer); // store_rest recebe a junção do store_rest(resto da 
		// leitura anterior) mais o novo buffer lido;
		free(temp_to_join); // damos free na variável temporária
		if (ft_strchr(buffer, '\n')) // se no buffer encontramos uma quebra de linha '\n'...
			break ; // paramos o while, saímos dele
	}
	return (store_rest); // retornamos o store_rest montado com o resto da linha anterior, mais o(s) próximos
	// buffer(s) lido(s), sendo que o último buffer adicionado tem a quebra de linha
}

// essa função separa a linha do resto lido ao encontrar um '\n', o restante que sobrou é colocada no temporariamente
// no rest_buffer e na função get_next_line é armazenada na variável estática.
static char	*separete_line_rest(char *line) // essa função recebe a linha que será aparada;
{
	char	*rest_line; // criamos um ponteiro de string que temporariamente guardará o que for 'descartado'
	// da linha
	int		i; // criamos um índice i para percorrer a linha;

	i = 0; // nosso índice se inicia em zero;
	while (line[i] != '\0' && line[i] != '\n') //equanto a linha[na posição i] não acabar (diferente de '\0'),
	// e também não for a quebra de linha 
		i++; // avançamos para a próxima casa
	if (line[i] == '\0' || line[1] == '\0') // se saiu do while acima e linha[na posição i] é p byte nulo, é por
	// que não encontramos a quebra de linha, e nesse caso não temos rest_buffer para retornar
		return (NULL); // então retornamos NULL
	rest_line = ft_substr(line, i + 1, ft_strlen(line) - i); //o resto da linha, rest_line, recebe a substring
	// da linha iniciando após o caracter \n e até o final da linha (de tamanho ft_strlen(line) - i)
	if (*rest_line== '\0') //se o que foi retirado da linha estiver vazio
	{
		free(rest_line); // damos um free nesse ponteiro rest_line
		rest_line = NULL; //e anulamos o ponteiro também (esta é uma boa prática, mas não é sempre necessário)
	}
	line[i + 1] = '\0'; // a posição i + 1, ou a próxima após a quebra de linha, recebe um \0, finalizando aqui a linha
	return (rest_line); // retornamos a linha
}

// A função read lê um bloco de leitura (x bytes) ou (BUFFER_SIZE) de cada vez.
char	*get_next_line(int fd) // a função de leitura recebe o fd passado por parâmetro
{
	char		*line; // criamos um ponteiro para a string que irá receber a linha;
	char		*buffer; // criamos um ponteiro para a string que irá armazenar o "bloco de leitura" da função read.
	static char	*store_rest // criamos um ponteiro para a string que armazenará o resto da linha, depois do
	// '\n', encontrado no último buffer adicionado na linha;
	// essa é uma VARIÁVEL ESTÁTICA, ou seja, ela não é zerada quando a função acaba, ela dura o tempo
	// de execussão do programa 

	if (fd < 0 || BUFFER_SIZE <= 0) // fazemos uma checagem de erro, caso o fd seja inválido (menor que 0)
	// ou o BUFFER_SIZE ou "bloco de leitura" seja menor ou igual a zero
		return (NULL); // devemos retornar NULL
	buffer = (char *) malloc((sizeof(char)) * (BUFFER_SIZE + 1)); // alocamos o espaço para armazenar o bloco lido, e mais o
	// byte nulo
	if (!buffer) //se função malloc não funcionou como deveria, ou seja, não conseguimos reservar por falta de memória
		return (NULL); // retornamos um ponteiro vazio
	line = read_buffers(fd, store_rest, buffer); // a linha recebe o retorno da função que chama repeditadamente
	// a função read e junta os buffers lidos em sequência, até que o último tenha a quebra de linha '\n';
	free(buffer); // limpamos a memória usada para a string buffer
	if (!line) // se a linha estiver vazia, provavelmente já acabou a leitura
		return (line); // retornamos a linha
	store_rest = separete_line_rest(line); //essa função midifica a linha, pois apara a linha no primeiro "\n" encontrado, e o restante, armazena
	// no store_rest;
	return (line); // temos a linha pronta para retornar;
}