## FBD blocks connecting rules
### connecting to inputs
1. graphic connecting
    - input

        ```xml
        <variable formalParameter="PT">
            <connectionPointIn>
                <relPosition x="0" y="50"/>
                    <connection refLocalId="7" formalParameter="OUT">
                        <position x="0" y="0"/>
                    </connection>
            </connectionPointIn>
        </variable>
        ```

      обязательные параметры в connectionPointIn->connection: `refLocalId="7"` и `formalParameter="OUT"`
    - output - no data
2. interface variable
    - input
      inside block variable (`CBlockVar`)
         ```xml
         <variable formalParameter="PT">
             <connectionPointIn>
                 <relPosition x="0" y="50"/>
                 <connection refLocalId="7">
                     <position x="640" y="230"/>
                 </connection>
             </connectionPointIn>
         </variable> 
         ```

      обязательные условия: connectionPointIn->connection: `refLocalId="7"` (обязательно непустое) `formalParameter` - 
      должен отсутствовать или быть пустым.
      `refLocalId` - ссылается на inVariable (CInVariable) вне блока внутри CBody:
      `CInVariable` - вне блока внутри body (CBody):

         ```xml
               <inVariable localId="7" executionOrderId="0" width="70" height="30" negated="false">
                   <position x="530" y="250"/>
                   <connectionPointOut>
                       <relPosition x="70" y="20"/>
                   </connectionPointOut>
                   <expression>InterfaceVariableName</expression>  <!-- here could be any constant too (don't know about string) -->
               </inVariable>```

3. constant
   a) real/time etc (not string)
    - input (inside the block - `CBlockVar`)

        ```xml
        <variable formalParameter="PT">
            <connectionPointIn>
                <relPosition x="0" y="50"/>
                <connection refLocalId="7">
                    <position x="640" y="230"/>
                </connection>
            </connectionPointIn>
        </variable>
        ```

      strict conditions: `connectionPointIn`->`connection`->`refLocalId="7"` (not empty), but no `fomal parameters`

      out of block inside the body `CInVariable`
       ```xml
       <inVariable localId="7" executionOrderId="0" width="70" height="30" negated="false">
             <position x="530" y="250"/>
         <connectionPointOut>
             <relPosition x="70" y="20"/>
         </connectionPointOut>
         <expression>T#480ms</expression>
       </inVariable>
       ```
> you should understand that connecting to the input of a constant or an interface variable looks the same in
> the `CBlockVar` with a little difference in the `CInVariable`. By the way, damned inOutVariables acts the same way - 
> they have both `connectionPointIn` and `connectionPointOut`, so `connectionPointIn` is our input variable's 
> `connectionPointIn`

b) array elements are not realized
c) string not defined
### connectg outputs

- __interface variables__
  intarface variable connection are described in `outVariable`:

    ```html
    <outVariable localId="33" executionOrderId="0" width="140" height="30" negated="false">
        <position x="680" y="940"/>
        <connectionPointIn>
            <relPosition x="0" y="10"/>
            <connection refLocalId="20" formalParameter="DONE">
                <position x="680" y="950"/> <!-- in our project there are no of positions -->
            </connection>
        </connectionPointIn>
        <expression>WRITE_DONE_FLAG</expression>
    </outVariable>
    ```
  >It is very important that each connected interface variable has a single `outVariable`. An interface variable can be 
  > connected to many outputs of a block, but with a single `outVariable`. Multiple connections are reflected in the 
  > tags `connectionPointIn`->`connection` as many connected blocks as `connection`. :+1:

  So interface variable is reflected in the `expression` tag. In our case is `WRITE_DONE_FLAG`.
  >Be careful, interface variable could be not from local POU interface, but global variable or alien POU interface 
  > variable

  connected block is described in `connection` tag. In our case is:
    ```xml 
    <connection refLocalId="20" formalParameter="DONE">
    ```
  it's mean block with `localId` = 20 and output name is `DONE`
- __graphic connecting__
  no special actions need. All data describing garphical connection is in the block inputs
- **inOutVariable**
  > Субъективно, но этот тип переменных придумали враги или недалёкие люди. Как и сам этот недостандарт

    ```xml
    <inOutVariable executionOrderId="0" height="24" localId="3" negatedIn="false" negatedOut="false" width="34">
        <position x="546" y="80"/>
        <connectionPointIn>
            <relPosition x="0" y="12"/>
            <connection formalParameter="OUT" refLocalId="4">
                <position x="546" y="92"/>
            </connection>
        </connectionPointIn>
        <connectionPointOut>
            <relPosition x="34" y="12"/>
        </connectionPointOut>
        <expression>Cnt</expression>
    </inOutVariable>
    ```

  В `inOutVariable` смотрим тэг `expression` - и понимаем, что за интерфейсную переменную хочет подцепить наша 
  `inOutVariable` C другой стороны этот тип переменных на "выходе" могут быть целями соединений и для других 
  `inOutVariable` и `outVariables`, да и сама эта inOut может цепляться как к блокам, так и к другим `inOutVariables`
  в общем можно программировать контроллеры многие годы и ниразу не использовать этот тип переменных, ну а сейчас это 
  причина для рекурсивного поиска, т.к. цепочка соединений с посощью `inOutVariable` может быть очень длинной.

  В общем случае `inOutVariable` не бывает конечной точкой (но кривой стандарт не запрещает ничего, поэтому может и быть), 
  в нашем случае, к этой переменной справа цеплялась `outVariable` и вместе с этой (эта переменная кстати идёт сразу в 
  блок) образуют две интерфейсные переменные на выходе блока

  > В целом алгоритм подключения выходов блока, за исключением прямых (графических соединений) выглядит так: перебираем 
  > `outVariables` и ищем в их `connection` блоки с выходами, если же встретили `inOutVariables`, это когда в 
  > `connection` `formalParameter` отсутствует или пуст, то сворачиваем с главной асфальтированной дороги на 
  > грунтовую рекурсию

P.S.: рекурсия это нормально, но вот к этому стандарту много вопросов.