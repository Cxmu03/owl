#ifndef OWL_VERTEXATTRIBUTE_HPP
#define OWL_VERTEXATTRIBUTE_HPP

template <typename T>
struct VertexAttribute {
    decltype(auto) GetType();
};

template <typename T>
decltype(auto) VertexAttribute<T>::GetType() {
    return T();
}

#endif //OWL_VERTEXATTRIBUTE_HPP
