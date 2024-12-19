//
// Created by artem on 19.12.24.
//

#ifndef PROCONT_CREMOVEOBJECT_H
#define PROCONT_CREMOVEOBJECT_H

#include <QUndoCommand>
#include "../graphics/COglWorld.h"

struct s_input_connection
{
    CPinIn      * pin{nullptr};
    CPinOut     * opposite{nullptr};
    CVariable   * variable{nullptr};
    QString       constant;
};

struct s_output_connection
{
    CPinOut * pin{nullptr};
    std::vector<CPinIn*>    opposites{};
    std::vector<CVariable*> variables{};
};

class CRemoveObject : public QUndoCommand
{
public:
    explicit CRemoveObject(CDiagramObject * object);
    ~CRemoveObject() override;

    void redo() override;
    void undo() override;

private:
    CDiagramObject  * m_object;
    CDiagramObject  * m_obj_to_delete{nullptr};
    COglWorld       * m_world;

    int               m_object_index{0};

    std::vector<s_input_connection>     m_input_connections;
    std::vector<s_output_connection>    m_output_connections;

    int     remove_object(CDiagramObject *object);
    void    insert_object(CDiagramObject *object, const int &index);

};


#endif //PROCONT_CREMOVEOBJECT_H
