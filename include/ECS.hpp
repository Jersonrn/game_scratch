#include <cstddef>



using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template<typename T>
inline ComponentID getComponentID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}
