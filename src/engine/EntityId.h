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

inline bool operator==(const EntityId &id1, const EntityId &id2) {
    return id1.index == id2.index && id1.version == id2.version;
}


#endif
