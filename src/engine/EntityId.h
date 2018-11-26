#ifndef ENTITYID_H_
#define ENTITYID_H_

struct EntityId {

    uint32_t index : 24;
    uint32_t version : 8;

};

inline std::ostream& operator<<(std::ostream &stream, const EntityId &id) {
    stream << "EntityId: { index : " << id.index << "}, { version : "
           << id.version << " }";
    return stream;
}


#endif
