//
// Created by artem on 10/20/24.
//

#ifndef EDITORSD_CDOCUMENTATION_H
#define EDITORSD_CDOCUMENTATION_H

#include "includes.h"

class CDocumentation
{
public:
    CDocumentation();
    CDocumentation(const CDocumentation & other);
    explicit CDocumentation(const QDomNode &node);
    ~CDocumentation();

    [[nodiscard]] QDomNode        dom_node() const;
    [[nodiscard]] bool            is_empty() const;
    QString                       documentation() const;
    void                          set_document(const QString &doc);

private:
    QString m_documentation;
};


#endif //EDITORSD_CDOCUMENTATION_H
