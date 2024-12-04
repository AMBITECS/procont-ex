### Todo
queue to `In progress...`
- start graphical connecting components.
- tuning
  - scaling support
  - put POUs into the `components palette`
  - Create 1000 ladders with components to test the responsiveness of the GUI
  - Multiselect support
- refactoring
- Adapt the class diagram and data flow in `UML` to the final form
- there are the rudiments of a design theme support system. It may be worth developing them.

### In progress...
- new/edit/reset variables on the components inputs/outputs

#### on pause
- реализовать сохранение диаграммы и интерфейса посредством сигналов главного виджета:
  ```c++
    class CDiagramWidget...
    signals:
    void    changed_diagram(const QDomNode & node); //!< diagram was changed
    void    changed_interface();                    //!< The interface has been changed from the diagram.
                                                    //!< It needs to be visually updated
    ```

### Done ✓
- ...
- edit components instance names and update it in the interface. (without tests)
- Реализовать в `CBlock` сохранение типов входных/выходных/вх.вых. переменных в теге `addData`
- Полная поддержка drag-drop выбранных объектов (без множественного выбора)
- realize `localId` to get current max `localId` everywhere. Seems to be `extern`.
- undo/redo via `Qt's Undo Framework` (с добавлением функционала undo/redo будет пополняться)
