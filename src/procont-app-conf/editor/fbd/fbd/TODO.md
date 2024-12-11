### Todo
queue to `In progress...`

- tuning
  - scaling support
  - put POUs into the `components palette`
  - Create 1000 visible_ladders with components to test the responsiveness of the GUI
  - Multiselect support
- refactoring
- Adapt the class diagram and data flow in `UML` to the final form


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
- graphical connecting components.
- тёмная и светлая темы. Определяется автоматически. Выставлять вручную нельзя (пока) 

### не забыть
 очень тонкий момент - в программе никак не отражен тот факт, что CBody в одном POU может быть несколько 
 (по стандарту, но не факт что так будет)