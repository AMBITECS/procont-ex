//
// Created by nechi on 29.11.2024.
//

#ifndef EDITORSD_CGRAPCHICSLOGIC_H
#define EDITORSD_CGRAPCHICSLOGIC_H


#include "CLadder.h"
#include "CConnectLine.h"

class CGraphicsLogic
{
public:
    CGraphicsLogic();
    ~CGraphicsLogic();

    /**@brief соединяет пины одной ступени иначе возвращает nullptr.  @attention возвращает объект во владение */
    CConnectLine*    add_new_line(CPin *dragged_pin, CPin *target_pin);

private:
    CLadder * m_ladder{nullptr};
    CPin    * m_dragged_pin{nullptr};
    CPin    * m_target_pin{nullptr};
    int object_bottom_max{0};

    /** @brief рисует горизонтальную линию от пина до области ЗА bound_text_rect */
    static QLine    first_line(CPin *pin, CPin *opp);
    /** @brief рисует линии-опуски от точек ЗА bound_text_rect до низа ступени (зависит от кол-ва линий внизу) */
    QLine down_line(const QPoint &upper_point);
    bool are_objects_near();
    void   direct_connection(CConnectLine *conn_line);

    static QLine equalizing_line(const QPoint &point1, const QPoint &point2);
    static int     index_of(std::vector<CPin*> *pins_array, CPin *pin);
};


#endif //EDITORSD_CGRAPCHICSLOGIC_H
