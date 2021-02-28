#ifndef _COMPLEMENTOS_
#define _COMPLEMENTOS_

#include <array>
#include <vector>
#include <random>
#include <cstring>

//#include <cryptopp810/cryptlib.h>
//#include <cryptopp810/sha.h>

//inline std::array < long long int, 5 > temposTrechos;

inline std::vector < unsigned char > concatenar(
	const std::vector < unsigned char > &dados1, const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados2)
{
	std::vector < unsigned char > concatenacao(dados1.size() + dados2.size());

	std::memcpy(concatenacao.data(), dados1.data(), dados1.size());
	std::memcpy(concatenacao.data() + dados1.size(), dados2.data(), dados2.size());

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const std::vector < unsigned char > &dados1, const std::vector < unsigned char > &dados2)
{
	std::vector < unsigned char > concatenacao(dados1.size() + dados2.size());

	std::memcpy(concatenacao.data(), dados1.data(), dados1.size());
	std::memcpy(concatenacao.data() + dados1.size(), dados2.data(), dados2.size());

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const std::vector < unsigned char > &dados1, const long long int &dados2)
{
	std::vector < unsigned char > concatenacao(dados1.size() + sizeof(long long int));

	std::memcpy(concatenacao.data(), dados1.data(), dados1.size());
	std::memcpy(concatenacao.data() + dados1.size(), &dados2, sizeof(long long int));

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const std::vector < unsigned char > &dados1, const unsigned char &dados2)
{
	std::vector < unsigned char > concatenacao(dados1.size() + sizeof(unsigned char));

	std::memcpy(concatenacao.data(), dados1.data(), dados1.size());
	std::memcpy(concatenacao.data() + dados1.size(), &dados2, sizeof(unsigned char));

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const long long int &dados1, const std::vector < unsigned char > &dados2)
{
	std::vector < unsigned char > concatenacao(sizeof(long long int) + dados2.size());

	std::memcpy(concatenacao.data(), &dados1, sizeof(long long int));
	std::memcpy(concatenacao.data() + sizeof(long long int), dados2.data(), dados2.size());

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const unsigned char &dados1, const std::vector < unsigned char > &dados2)
{
	std::vector < unsigned char > concatenacao(sizeof(unsigned char) + dados2.size());

	std::memcpy(concatenacao.data(), &dados1, sizeof(unsigned char));
	std::memcpy(concatenacao.data() + sizeof(unsigned char), dados2.data(), dados2.size());

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(const long long int &dados1, const long long int &dados2)
{
	std::vector < unsigned char > concatenacao(sizeof(long long int) * 2);

	std::memcpy(concatenacao.data(), &dados1, sizeof(long long int));
	std::memcpy(concatenacao.data() + sizeof(long long int), &dados2, sizeof(long long int));

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(const unsigned char &dados1, const unsigned char &dados2)
{
	std::vector < unsigned char > concatenacao(sizeof(unsigned char) * 2);

	std::memcpy(concatenacao.data(), &dados1, sizeof(unsigned char));
	std::memcpy(concatenacao.data() + sizeof(unsigned char), &dados2, sizeof(unsigned char));

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados1, const unsigned char &dados2)
{
	std::vector < unsigned char > concatenacao(dados1.size() + sizeof(unsigned char));

	std::memcpy(concatenacao.data(), dados1.data(), dados1.size());
	std::memcpy(concatenacao.data() + dados1.size(), &dados2, sizeof(unsigned char));

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados1, const long long int &dados2)
{
	std::vector < unsigned char > concatenacao(dados1.size() + sizeof(long long int));

	std::memcpy(concatenacao.data(), dados1.data(), dados1.size());
	std::memcpy(concatenacao.data() + dados1.size(), &dados2, sizeof(long long int));

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados1, const std::vector < unsigned char > &dados2)
{
	std::vector < unsigned char > concatenacao(dados1.size() + dados2.size());

	std::memcpy(concatenacao.data(), dados1.data(), dados1.size());
	std::memcpy(concatenacao.data() + dados1.size(), dados2.data(), dados2.size());

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados1,
	const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados2)
{
	std::vector < unsigned char > concatenacao(dados1.size() + dados2.size());

	std::memcpy(concatenacao.data(), dados1.data(), dados1.size());
	std::memcpy(concatenacao.data() + dados1.size(), dados2.data(), dados2.size());

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const long long int &dados1, const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados2)
{
	std::vector < unsigned char > concatenacao(sizeof(long long int) + dados2.size());

	std::memcpy(concatenacao.data(), &dados1, sizeof(long long int));
	std::memcpy(concatenacao.data() + sizeof(long long int), dados2.data(), dados2.size());

	return concatenacao;
}

inline std::vector < unsigned char > concatenar(
	const std::string &dados1, 
        const long int &dados2)
{
	std::vector < unsigned char > concatenacao(sizeof(long int) + dados1.size());
        const char * dado1 = dados1.c_str();
        int size = dados1.size();

	std::memcpy(concatenacao.data(), dado1, size);
	std::memcpy(concatenacao.data() + size, (const void *) &dados2, sizeof(long int));

	return concatenacao;
}

inline std::vector < unsigned char > ouExclusivo(
	const std::vector < unsigned char > &dados1, const std::vector < unsigned char > &dados2)
{
	const size_t quantidadeMinimaBytes = std::min(dados1.size(), dados2.size());

	std::vector < unsigned char > resultado(quantidadeMinimaBytes);

	for (size_t i = 0; i < quantidadeMinimaBytes; i++)
	{
		resultado[i] = dados1[i] ^ dados2[i];
	}

	return resultado;
}

inline std::array < unsigned char, sizeof(unsigned char) * 32 > ouExclusivo(
	const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados1,
	const std::array < unsigned char, sizeof(unsigned char) * 32 > &dados2)
{
	std::array < unsigned char, sizeof(unsigned char) * 32 > resultado{};

	for (size_t i = 0; i < 32; i++)
	{
		resultado[i] = dados1[i] ^ dados2[i];
	}

	return resultado;
}

inline std::array < unsigned char, sizeof(unsigned char) * 32 > numeroAleatorio()
{
	std::array < unsigned char, sizeof(unsigned char) * 32 > _numeroAleatorio{};
	std::random_device dispositivoAleatorio;

	for (size_t i = 0; i < 32; i += sizeof(std::random_device::result_type))
	{
		const auto valorAleatorio = dispositivoAleatorio();

		std::memmove(_numeroAleatorio.data() + i, &valorAleatorio, sizeof(std::random_device::result_type));
	}

	return _numeroAleatorio;
}

struct HashArray32
{
	size_t operator()(const std::array < unsigned char, sizeof(unsigned char) * 32 > &UID) const noexcept
	{
		size_t hash = 0;

		for (const auto &elemento : UID)
		{
			hash ^= elemento;
		}

		return hash;
	}
};


#endif