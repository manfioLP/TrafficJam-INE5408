//! COPYRIGHT @LeopoldoManfio #2018

#ifndef TRAFFICJAM_ARRAYLIST_H
#define TRAFFICJAM_ARRAYLIST_H

#include <cstdint>
#include <stdexcept>
//! Classe Lista
/*!
 * Classe responsavel por:
 *  -ordenar dados.
 *  -inserir ou retirar dados de qualquer posiçao,
 * A classe e baseada em um indice que assume valor 0 quando a lista estiver vazia.
 */

 template <typename T>
 class ArrayList {
 public:
     explicit ArrayList();
     explicit ArrayList(std::size_t max_size);
     ~ArrayList();

     void clear();
     void push_back(const T& data);
     void push_front(const T& data);
     void insert(const T& data, std::size_t index);
     void insert_sorted(const T& data);
     T pop(std::size_t index);
     T pop_back();
     T pop_front();
     void remove(const T& data);
     bool full() const;
     bool empty() const;
     bool contains(const T& data) const;
     std::size_t find(const T& data) const;
     std::size_t size() const;
     std::size_t max_size() const;
     T& at(std::size_t index);
     T& operator[](std::size_t index);
     const T& at(std::size_t index) const;
     const T& operator[](std::size_t index) const;

 private:
     T* contents;  //! Tipo generico para armazenar a lista.
     std::size_t size_;  //! Indicador de posiçao da lista
     std::size_t max_size_;  //! Tamanho maximo da lista

     static const auto DEFAULT_MAX = 10u; //!< Tamanho padrão da lista.
 };

//! Construtor padrão
/*!
 * A lista e inicializada usando DEFAULT_MAX
 */
template<typename T>
ArrayList<T>::ArrayList() {
    ArrayList(DEFAULT_MAX);
}

//! Construtor passando o tamanho da lista.
/*! Inicia a lista passando um valor de max_size,
 * inicializa o array generico e seta o indicador de posiçao para zero.
 *
 */
template<typename T>
ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0u;
}

//! Destrutor
/*! Destrutor padrao, deleta o array generico.
 */
template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] contents;
}

//! Esvazia a lista.
/*! Seta o tamanho da lista para zero, sobrescrevendo os valores antigos caso necessario.
 */
template<typename T>
void ArrayList<T>::clear() {
    size_ = 0u;
}

//! Inserçao no fim da lista
/*!
 * caso a lista esteja cheia, lança um std_out_of_range exception,
 * caso seja possivel inserir dados, chama o metodo insert, passando
 * como posiçao o tamanho atual da lista.
 * @tparam T
 * @param data -> contem o dado a ser inserido na lista
 */
template<typename T>
void ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia!");
    insert(data, size());
}

//! Inserção no começo da lista.
/*!
 * similar ao push_back(), chama o metodo insert
 * e lança std::out_of_range caso esteja cheia.
 * @tparam T
 * @param data  -> contem o dado a ser inserido na lista
 */
template<typename T>
void ArrayList<T>::push_front(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia!");
    insert(data, 0u);
}

//! Inserção em posiçao especificada
/*! Testa se a posição e válida, se sim e a lista se reorganiza e insere.
 *  Caso:
 *   -O índice não existir,
 *   -A lista estiver cheia,
 *   Lança um std::out_of_range exception
 *  \param data um dado T que será inserido na lista.
 *  \param index -> indican a posição que será inserido o dado.
 */
template<typename T>
void ArrayList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Posição não existe!");

    if (full())
        throw std::out_of_range("Lista cheia!");

    for (int atual = size_; atual > index; atual--)
        contents[atual] = contents[atual-1];
    size_++;
    contents[index] = data;
}

//! Inserção ordenada na lista.
/*!
 * Busca a posiçao desejada e vai testando se continua em ordem, entao chama o metodo insert.
 * Pode lançar todos os erros de insert, mas se a lista estiver cheia,
 * lança um erro antes mesmo de chamar insert.
 * @tparam T
 * @param data -> dado a ser inserido
 */

template<typename T>
void ArrayList<T>::insert_sorted(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia!");

    std::size_t index = 0u;
    while (index < size_ && data > contents[index])
        index++;
    insert(data, index);
}

//! Remove e retorno o dado de uma posição específica da lista.
/*!
 * Verifica se o index desejado e valido, entao busca o dado, adiciona o mesmo a uma variavel
 * temporaria e retorna, depois decrementa size_;
 * @tparam T
 * @param index
 * @return dado removido
 */
template<typename T>
T ArrayList<T>::pop(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista vazia!");

    size_--;
    T tmp = contents[index];
    for (auto atual = index; atual < size_; atual++)
        contents[atual] = contents[atual+1];
    return tmp;
}

//! Remove e retorno ultimo dado da lista
/*!
 * Testa se a lista esta vazia e entao retorna a funçao pop,
 * passando como parametro size_ -1.
 * Se a lista estiver vazia lança std::out_of_range.
 * @tparam T
 * @return dado retornado de pop()
 */
template<typename T>
T ArrayList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("Lista vazia!");
    return pop(size_-1);
}


//! Remove e retorna primeiro dado da lista
/*!
 * se a lista estiver vazia, lança um std_out_of_range exception,
 * senao, chama o metodo pop com parametro 0 e retorna.
 * @tparam T
 * @return dado retornado por pop()
 */
template<typename T>
T ArrayList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia!");
    return pop(0u);
}

//! Remoção de um dado da lista.
/*! Busca o índice do dado e remove ele da lista utilizando pop.
 * Porem antes testa se contem o dado e se a lista nao esta vazia.
 *  @paramt T
 *  @param data um dado T que será removido da lista.
 */
template<typename T>
void ArrayList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Lista vazia!");
    if (!contains(data))
        throw std::out_of_range("Dado não encontrado!");

    std::size_t index = find(data);
    pop(index);
}

//! Lista cheia
/*! Testa se a lista está cheia.
 *  @return bool
 */
template<typename T>
bool ArrayList<T>::full() const {
    return size_ == max_size_;
}

//! Lista vazia
/*! Testa se a lista está vazia.
 * @return bool
 */
template<typename T>
bool ArrayList<T>::empty() const {
    return size_ == 0u;
}

//! Contém dado
/*! Testa se um dado está na lista.
 * @return bool, true caso existe, false caso nao.
 */
template<typename T>
bool ArrayList<T>::contains(const T& data) const {
    return find(data) != size_;
}

//! lista vazia
/*! busca o elemento e retorna sua posiçao
 *  @return index do elemento
 */
template<typename T>
std::size_t ArrayList<T>::find(const T& data) const {
    std::size_t index = 0u;
    while (index < size_) {
        if (contents[index] == data)
            break;
        index++;
    }
    return index;
}

//! Tamanho da lista.
/*! Retorna o tamanho (size_) da lista.
 * @return size_
 */
template<typename T>
std::size_t ArrayList<T>::size() const {
    return size_;
}

//! Tamanho máximo da lista.
/*! Retorna o maior tamanho possível da lista (max_size_).
 * @return max_size;
 */
template<typename T>
std::size_t ArrayList<T>::max_size() const {
    return max_size_;
}

//! Referencia o dado na posição da lista.
/*! Retorna o dado que esta na posição da lista para uso externo, caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 */
template<typename T>
T& ArrayList<T>::at(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista Vazia!");
    return contents[index];
}

//! Referencia o dado na posição da lista.
/*! Retorna o dado que esta na posição da lista para uso externo, caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \return T& um dado que será referenciado.
 *  \sa at(), at() const, operator[]() const
 */
template<typename T>
T& ArrayList<T>::operator[](std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista Vazia!");
    return contents[index];
}

//! Referencia o dado na posição da lista.
/*! Retorna o dado que esta na posição da lista para uso externo, caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \return T& um dado que será referenciado.
 *  \sa at(), operator[](), operator[]() const
 */
template<typename T>
const T& ArrayList<T>::at(std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista Vazia!");
    return contents[index];
}

//! Referencia o dado na posição da lista.
/*! Retorna o dado que esta na posição da lista para uso externo, caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \return T& um dado que será referenciado.
 *  \sa at(), operator[](), at() const
 */
template<typename T>
const T& ArrayList<T>::operator[](std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista Vazia!");
    return contents[index];
}

#endif //TRAFFICJAM_ARRAYLIST_H
