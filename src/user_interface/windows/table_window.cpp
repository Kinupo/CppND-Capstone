#include "user_interface/windows/table_window.h"

TableWindow::TableWindow(std::string name, int max_cols, int max_rows, int x_pos, int y_pos)
    : Window(name, x_pos, y_pos, max_cols, max_rows){
    _window = newwin(max_rows, max_cols, y_pos, x_pos);
}

TableWindow::~TableWindow(){}

void TableWindow::TableData(int row_num, std::unique_ptr<Row> row){
    if(_rows.size() >= row_num -1 && row_num -1 >= 0){
        _rows[row_num -1] =std::move(row);
        _was_touched = true;
    }
}

void TableWindow::TableData(std::vector<std::unique_ptr<Row>> rows){
    _rows = std::move(rows);
    _was_touched = true;
}

void TableWindow::TableData(std::vector<std::unique_ptr<std::vector<std::string>>> rows){
     _rows.clear();
     _selected = std::vector<std::string>();
    for(auto& row_data:rows){
        auto row = std::make_unique<Row>();
        row->data = *row_data;
        _rows.emplace_back(std::move(row));
    }
    _was_touched = true;
}

void TableWindow::Title(std::string title){
    _title = title;
    _was_touched = true;
}

void TableWindow::Columns(std::vector<std::unique_ptr<Column>> columns){
    _columns = std::move(columns);
    _was_touched = true;
}

void TableWindow::DrawTitle(){
    mvwprintw(_window, 1, 2, _title.c_str());
    wmove(_window, 2, 2);
    whline(_window, ACS_HLINE, _window->_maxx -2);
}

void TableWindow::DrawColumnHeaders(){
    int x_pos = 2;
    for(auto& column:_columns){
        mvwprintw(_window, 3, x_pos, column->name.c_str());
        x_pos += column->width +2;
    }

    wmove(_window, 4, 2);
    whline(_window, ACS_HLINE, _window->_maxx -2);
}

void TableWindow::DrawRows(){
    int y_pos = 5;
    for(auto& row:_rows){
        DrawRow(*row.get(), y_pos++);
    }
}

void TableWindow::DrawRow(Row& row, int y_pos){
    int x_pos = 2;
    for(int i =0;i < row.data.size(); i++){
        if(_columns.size() <= i)
            break;
        auto row_data = row.data[i];
        mvwprintw(_window, y_pos, x_pos, row_data.c_str());
        x_pos += _columns[i]->width +2;
    }
}

void TableWindow::ForceDraw(){
    box(_window, 0, 0);

    DrawTitle();
    DrawColumnHeaders();
    DrawRows();
    
	wnoutrefresh(_window);
}

//Return row
bool TableWindow::ProcessClick(MEVENT& mouse_event){
    if(mouse_event.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED | BUTTON1_RELEASED)){

        auto maximum_rows = _max_rows == 0 ? (_window->_maxy - _y_pos): _max_rows;
        auto selectable_row_count = _rows.size() < maximum_rows -6 ? _rows.size() : maximum_rows -6;
        auto maximum_columns = _max_cols == 0 ? _window->_maxx - _x_pos: _max_cols;

        auto x_mouse_position = mouse_event.x + 1;
        auto y_mouse_position = mouse_event.y + 1;
        
        //todo: make column selectable
        if(y_mouse_position > (_y_pos +5) //first selectable row
            && y_mouse_position <= (selectable_row_count + _y_pos +5)//last selectable row
            && x_mouse_position > (_x_pos +1)
            && x_mouse_position < (maximum_columns + _x_pos)){
            _selected = _rows.at(y_mouse_position -_y_pos -6)->data;
            return true;
        } else {
            //it is clearing the slected before being processed
            // _selected = std::vector<std::string>();
        }
    }
    return false;
}

std::vector<std::string> TableWindow::Selected(){
    auto current_selected = _selected;
    _selected = std::vector<std::string>();
    return current_selected;
}