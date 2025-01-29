//
// Created by artem on 12.10.24.
//

#ifndef EDITORSD_COGLSTYLE_H
#define EDITORSD_COGLSTYLE_H

struct s_color
{
    float red{0};
    float green{0};
    float blue{0};
    float alpha{1};
};

class COglStyle
{
public:
    COglStyle();
    ~COglStyle();

    s_color   background();

protected:

private:

};


#endif //EDITORSD_COGLSTYLE_H
