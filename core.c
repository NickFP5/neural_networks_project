%-----GENERAZIONE INPUT E OUTPUT AGLI ISTANTI PRECEDENTI
if ritardi_output ~=0
j=1+ (ritardi_output)- (ritardi_input) 
else
 j=1   
end
 
input_train=[] %inizializzo vettore di appoggio
input_test=[]
for i= ritardi_input:-1:0    %for(i=ritardi_input; i==0 ; i-- )
    input_train= [inputl(j:end-i,1) input_train];
    input_test= [inputt(j:end-i,1) input_test];
    j=j+1   
end
output_train=[]
output_test=[]
if ritardi_output ~=0 
j=1
else 
j= 1+ritardi_input;   
end
 
for i= ritardi_output:-1:0  %for(i=ritardi_output; i==0 ; i-- )
    output_train= [outputl(j:end-i,1) output_train];
    output_test= [outputt(j:end-i,1) output_test];
    j=j+1
end   
input_train = [input_train output_train(:,2:end)];
input_test = [input_test output_test(:,2:end)];


%-------GENERAZIONE RETE E LEARNING
Rete = newff(input_train',(output_train(:,1))',neuroni); %creo nuova rete
Rete.trainParam.show= show; %imposto parametro show
Rete.trainParam.lr=lr; %imposto parametro lr
Rete.trainParam.epochs=epochs; %imposto parametro epochs
Rete = train(Rete,input_train',(output_train(:,1))'); %learning rete
 
output_rete= Rete(input_train') %genero output dalla rete post learning
assignin('base','output_rete',output_rete)
performancel =perform(Rete, output_rete, (output_train(:,1))') 
set(handles.edit17,'String',num2str(performancel))
 
output_rete_t= Rete(input_test') %genero output dalla rete post leatning passandogli gli input di test
assignin('base','output_rete_t',output_rete_t)
performancet =perform(Rete, output_rete_t, (output_test(:,1))') 
set(handles.edit18,'String',num2str(performancet))
 
set(handles.edit20,'String',avviso)
 
%-------- ERRORI
 
errore_l = output_rete - (output_train(:,1)')
assignin('base','errore_l',errore_l)
 
errore_t = output_rete_t - (output_test(:,1)')
assignin('base','errore_t',errore_t)

