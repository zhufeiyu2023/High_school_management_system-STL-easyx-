#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <graphics.h>
#include<vector>
inline void changeprecistion(std::wstring& ws, int precision) {
    auto len = ws.length(); int i = 0;
    for (; i < len; i++) {
        if (ws[i] == '.')
            break;
    }
    if (i + precision + 1 >= len)
        return;
    ws = ws.substr(0, ((((size_t)(i + precision + 1)) < (len)) ? ((size_t)(i + precision + 1)) : (len)));
}
template<typename RandomIt>
inline void analysis(RandomIt begin, RandomIt end, std::wstring title = L"统计图")
{
    int size = int(end - begin); auto& arr = begin;
    // 初始化图形模式
    initgraph(1000, 600, SHOWCONSOLE);  // 可以根据需要调整窗口大小
    setbkcolor(WHITE);
    cleardevice();
    setlinecolor(BLACK);
    int margin_top = 40;
    int margin_bottom = 60;
    int margin_left = 70;
    int margin_right = 30;
    int width = getwidth();
    int height = getheight();
    int 柱状图可分配宽度 = width - margin_left - margin_right;
    int 柱状图可分配高度 = height - (margin_top + margin_bottom);
    int 每个柱子可用宽度 = 柱状图可分配宽度 / size;
    double maxData = 0;
    const int size1 = 22, size2 = 32;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > maxData) {
            maxData = arr[i];
        }
    }
    maxData = maxData == 0 ? 1 : maxData;
    double scale = static_cast<double>(柱状图可分配高度) / static_cast<double>(maxData);

    // 计算应该显示的刻度值
    double interval = 50.0;  // 调整为合适的刻度间隔
    double remainder = fmod(maxData, interval);
    double maxScale = maxData;
    if (remainder != 0) {
        maxScale = maxData + interval - remainder; // 将最大值扩展到刻度值的整数倍
    }

    // 绘制标题


    settextstyle(size2, 0, _T("微软雅黑"));
    settextcolor(BLACK);
    RECT r = { 0, 0, width, 50 };
    drawtext(title.c_str(), &r, DT_CENTER | DT_VCENTER);

    settextstyle(size1, 0, _T("微软雅黑"));
    std::wstring ttt;
    ttt = std::to_wstring(maxData);
    r = { 0, margin_top - 10, margin_left,margin_top + 30 };
    //在统计图y轴表示刻度
    line(r.right - 20, r.top + size1 / 2, r.right - 10, r.top + size1 / 2);
    changeprecistion(ttt, 1);
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);

    ttt = std::to_wstring(maxData / 2);
    r = { 0, margin_top + 柱状图可分配高度 / 2 - 10, margin_left,margin_top + 柱状图可分配高度 / 2 + 30 };
    line(r.right - 20, r.top + size1 / 2, r.right - 10, r.top + size1 / 2);
    changeprecistion(ttt, 1);
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);

    ttt = std::to_wstring(maxData / 4 * 3);
    r = { 0, margin_top + 柱状图可分配高度 / 4 - 10, margin_left,margin_top + 柱状图可分配高度 / 4 + 30 };
    line(r.right - 20, r.top + size1 / 2, r.right - 10, r.top + size1 / 2);
    changeprecistion(ttt, 1);
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);

    ttt = std::to_wstring(maxData / 4);
    r = { 0, margin_top + 柱状图可分配高度 / 2 + 柱状图可分配高度 / 4 - 10, margin_left,margin_top + 柱状图可分配高度 / 2 + 柱状图可分配高度 / 4 + 30 };
    line(r.right - 20, r.top + size1 / 2, r.right - 10, r.top + size1 / 2);
    changeprecistion(ttt, 1);
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);
    //标记原点
    ttt = L"0";
    r = { 0, margin_top + 柱状图可分配高度 - 10, margin_left,margin_top + 柱状图可分配高度 + 30 };
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);


    // 计算比例因子
    scale = static_cast<double>(柱状图可分配高度) / static_cast<double>(maxData);

    settextstyle(size1, 0, _T("Times New Roman"));
    // chart
    for (int i = 0; i < size; ++i) {

        int x1 = margin_left + i * 每个柱子可用宽度 + 每个柱子可用宽度 / 5;

        int x2 = x1 + 每个柱子可用宽度 - 每个柱子可用宽度 / 5;
        int y2 = margin_top + 柱状图可分配高度;
        int y1 = y2 - arr[i] * int(scale);
        setfillcolor(BLUE);
        fillrectangle(x1, y1, x2, y2);
        settextcolor(BLACK);

        wchar_t msg[50];
        wsprintfW(msg, L"%.1f", arr[i]);
        RECT r = { x1, y1 - 20, x2,y1 };
        drawtext(msg, &r, DT_CENTER | DT_VCENTER);
        drawtext(L" ", &r, DT_CENTER | DT_VCENTER);
        wsprintfW(msg, L"第%d次", i + 1);

        r = { x1, y2 + 20, x2,y2 + 40 };
        drawtext(msg, &r, DT_CENTER | DT_VCENTER);
    }

    //x

    line(margin_left - 10, margin_top + 柱状图可分配高度 + 10, width - margin_right + 10, margin_top + 柱状图可分配高度 + 10
    );
    line(width - margin_right + 2,
        margin_top + 柱状图可分配高度 + 2,
        width - margin_right + 10,
        margin_top + 柱状图可分配高度 + 10
    );
    line(width - margin_right + 2,
        margin_top + 柱状图可分配高度 + 18,
        width - margin_right + 10,
        margin_top + 柱状图可分配高度 + 10
    );
    // y
    line(margin_left - 10, margin_top, margin_left - 10, margin_top + 柱状图可分配高度 + 10
    );
    line(margin_left - 10,
        margin_top,
        margin_left - 18,
        margin_top + 8
    );
    line(margin_left - 10,
        margin_top, margin_left - 2,
        margin_top + 8
    );
    //原点
    fillcircle(margin_left - 10, margin_top + 柱状图可分配高度 + 10, 3); std::wcin >> ttt; closegraph();
}

