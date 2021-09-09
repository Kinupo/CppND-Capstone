#ifndef _USER_INTERFACE_WINDOWS_TABLE_WINDOW_H_
#define _USER_INTERFACE_WINDOWS_TABLE_WINDOW_H_

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "user_interface/windows/column.h"
#include "user_interface/windows/row.h"
#include "user_interface/window.h"

class TableWindow : public Window {
    private:              
        std::string _title;
        std::vector<std::unique_ptr<Column>> _columns;
        std::vector<std::unique_ptr<Row>> _rows;

        std::vector<std::string> _selected = std::vector<std::string>();

        void DrawTitle();
        void DrawColumnHeaders();
        void DrawRows();
        void DrawRow(Row& row, int y_pos);

    public:
        TableWindow(std::string name, int width, int height, int x_pos, int y_pos);
        ~TableWindow();

        void TableData(int row_num, std::unique_ptr<Row> row);
        void TableData(std::vector<std::unique_ptr<Row>> rows);
        void TableData(std::vector<std::unique_ptr<std::vector<std::string>>> rows);

        void Title(std::string title);
        void Columns(std::vector<std::unique_ptr<Column>> column);

        void ForceDraw();

        bool ProcessClick(MEVENT& mouse_event);

        //returns the row data for the selected row
        std::vector<std::string> Selected();
};

#endif