function convgui()
% This is the machine-generated representation of a Handle Graphics object
% and its children.  Note that handle values may change when these objects
% are re-created. This may cause problems with any callbacks written to
% depend on the value of the handle at the time the object was saved.
%
% To reopen this object, just type the name of the M-file at the MATLAB
% prompt. The M-file and its associated MAT-file must be on your path.

a = figure('Color',[0.8 0.8 0.8], ...
   'CreateFcn','dconvdemo_callbacks SetFigureSize', ...
   'IntegerHandle','off', ...
   'KeyPressFcn','dconvdemo_callbacks KeyPressFcn', ...
   'MenuBar','none', ...
	'Name','Discrete Time Convolution Demo', ...
	'NumberTitle','off', ...
   'Tag','DCONVDEMO');
b = uimenu('Parent',a, ...
	'Label','&Plot &Options', ...
   'Tag','Plot Options');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Checked','off', ...
   'Label','Show &Circular Convolution', ...
   'Tag','Circular Mode');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Label','&Tutorial Mode', ...
   'Separator','on', ...
   'Tag','Tutorial Mode');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Label','&Conserve Space', ...
   'Separator','on', ...
   'Tag','Conserve Space');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Label','&Grid On', ...
	'Tag','Grid On');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Enable','off', ...
   'Label','&Reset Axes', ...
	'Tag','Reset Axes');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Enable','on', ...
   'Label','&Set Line Width...', ...
   'Tag','Set Line Width');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Enable','on', ...
   'Label','&Set Font Size...', ...
   'Tag','Set Font Size');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Enable','on', ...
   'Label','&Take Screen-shot', ...
   'Tag','Screenshot');
c = uimenu('Parent',b, ...
   'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
   'Enable','on', ...
   'Label','&Show Menu', ...
   'Tag','ShowMenu');
b = uimenu('Parent',a, ...
	'Label','&Help', ...
   'Tag','Help');
c = uimenu('Parent',b, ...
    'Callback','dconvdemo_callbacks(get(gcbo,''Tag''));', ...
    'Label','&Contents...', ...
    'Tag','Help');  
b = axes('Parent',a, ...
   'Units','normalized', ...
   'Box','on', ...
	'CameraUpVector',[0 1 0], ...
   'CameraUpVectorMode','manual', ...
   'CreateFcn','dconvdemo_callbacks InitTextBox', ...
   'Color',[.95 .95 .95], ...
   'NextPlot','replacechildren', ...
   'Position',[0.63 0.18 0.35 0.31], ...
   'Tag','TextAxis', ...
   'XColor',[0 0 0], ...
   'XTick',[], ...
   'YColor',[0 0 0], ...
   'YDir','reverse', ...
   'YTick',[], ...
   'ZColor',[0 0 0], ...
   'ZTick',[]);
c = text('Parent',b, ...
   'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[-0.152439 -0.20339 0], ...
	'Tag','TextAxisXLabel', ...
	'VerticalAlignment','cap');
set(get(c,'Parent'),'XLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[-29.4207 0.491525 0], ...
	'Rotation',90, ...
	'Tag','TextAxisYLabel', ...
	'VerticalAlignment','baseline');
set(get(c,'Parent'),'YLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','right', ...
	'Position',[-26.8293 1.08475 0], ...
	'Tag','TextAxisZLabel', ...
	'Visible','off');
set(get(c,'Parent'),'ZLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[-0.152439 1.05932 0], ...
	'Tag','TextAxisTitle', ...
	'VerticalAlignment','bottom');
set(get(c,'Parent'),'Title',c);
b = axes('Parent',a, ...
	'CameraUpVector',[0 1 0], ...
   'CameraUpVectorMode','manual', ...
   'Color',[1 1 1], ...
   'CreateFcn','dconvdemo_callbacks InitAxis', ...
   'NextPlot','replacechildren', ...
	'Position',[0.05 0.683333 0.53 0.266667], ...
   'Tag','SignalAxis', ...
   'XColor',[0 0 0], ...
   'XTickLabel','', ...
   'YColor',[0 0 0], ...
	'ZColor',[0 0 0], ...
    'Box','On');
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[-0.152439 -0.20339 0], ...
	'Tag','SignalAxisXLabel', ...
	'VerticalAlignment','cap');
set(get(c,'Parent'),'XLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[-29.4207 0.491525 0], ...
	'Rotation',90, ...
	'Tag','SignalAxisYLabel', ...
	'VerticalAlignment','baseline');
set(get(c,'Parent'),'YLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','right', ...
	'Position',[-26.8293 1.08475 0], ...
	'Tag','SignalAxisZLabel', ...
	'Visible','off');
set(get(c,'Parent'),'ZLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[-0.152439 1.05932 0], ...
	'Tag','SignalAxisTitle', ...
	'VerticalAlignment','bottom');
set(get(c,'Parent'),'Title',c);
b = axes('Parent',a, ...
	'CameraUpVector',[0 1 0], ...
	'CameraUpVectorMode','manual', ...
	'Color',[1 1 1], ...
   'CreateFcn','dconvdemo_callbacks InitAxis', ...
   'NextPlot','replacechildren', ...
	'Position',[0.05 0.366667 0.53 0.266667], ...
	'Tag','MultiplyAxis', ...
   'XColor',[0 0 0], ...
   'XTickLabel','', ...
	'YColor',[0 0 0], ...
	'ZColor',[0 0 0], ...
    'Box','On');
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-0.0764526 -0.205128 0], ...
	'Tag','MultiplyAxisXLabel', ...
	'VerticalAlignment','cap');
set(get(c,'Parent'),'XLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-29.4343 0.487179 0], ...
	'Rotation',90, ...
	'Tag','MultiplyAxisYLabel', ...
	'VerticalAlignment','baseline');
set(get(c,'Parent'),'YLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','right', ...
	'Interruptible','off', ...
	'Position',[-26.8349 2.33333 0], ...
	'Tag','MultiplyAxisZLabel', ...
	'Visible','off');
set(get(c,'Parent'),'ZLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-0.0764526 1.05983 0], ...
	'Tag','MultiplyAxisTitle', ...
	'VerticalAlignment','bottom');
set(get(c,'Parent'),'Title',c);
b = axes('Parent',a, ...
	'CameraUpVector',[0 1 0], ...
	'CameraUpVectorMode','manual', ...
	'Color',[1 1 1], ...
    'CreateFcn','dconvdemo_callbacks InitAxis', ...
    'NextPlot','replacechildren', ...
	'Position',[0.05 0.05 0.53 0.266667], ...
	'Tag','OutputAxis', ...
	'XColor',[0 0 0], ...
	'YColor',[0 0 0], ...
	'ZColor',[0 0 0], ...
    'Box','On');
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-0.0764526 -0.205128 0], ...
	'Tag','OutputAxisXLabel', ...
	'VerticalAlignment','cap');
set(get(c,'Parent'),'XLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-29.4343 0.487179 0], ...
	'Rotation',90, ...
	'Tag','OutputAxisYLabel', ...
	'VerticalAlignment','baseline');
set(get(c,'Parent'),'YLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','right', ...
	'Interruptible','off', ...
	'Position',[-27.2936 3.57265 0], ...
	'Tag','OutputAxisZLabel', ...
	'Visible','off');
set(get(c,'Parent'),'ZLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-0.0764526 1.05983 0], ...
	'Tag','OutputAxisTitle', ...
	'VerticalAlignment','bottom');
set(get(c,'Parent'),'Title',c);
b = axes('Parent',a, ...
	'CameraUpVector',[0 1 0], ...
	'CameraUpVectorMode','manual', ...
	'Color',[1 1 1], ...
   'CreateFcn','dconvdemo_callbacks InitAxis', ...
   'NextPlot','replacechildren', ...
	'Position',[0.05 0.05 0.53 0.266667], ...
   'Tag','CircularOutputAxis', ...
   'Visible','off', ...
	'XColor',[0 0 0], ...
	'YColor',[0 0 0], ...
	'ZColor',[0 0 0]);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-0.0764526 -0.205128 0], ...
	'Tag','CircularOutputAxisXLabel', ...
	'VerticalAlignment','cap');
set(get(c,'Parent'),'XLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-29.4343 0.487179 0], ...
	'Rotation',90, ...
	'Tag','CircularOutputAxisYLabel', ...
	'VerticalAlignment','baseline');
set(get(c,'Parent'),'YLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','right', ...
	'Interruptible','off', ...
	'Position',[-27.2936 3.57265 0], ...
	'Tag','CircularOutputAxisZLabel', ...
	'Visible','off');
set(get(c,'Parent'),'ZLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Interruptible','off', ...
	'Position',[-0.0764526 1.05983 0], ...
	'Tag','CircularOutputAxisTitle', ...
	'VerticalAlignment','bottom');
set(get(c,'Parent'),'Title',c);
b = axes('Parent',a, ...
	'CameraUpVector',[0 1 0], ...
	'CameraUpVectorMode','manual', ...
	'Color',[1 1 1], ...
   'NextPlot','replacechildren', ...
	'Position',[0.63 0.73 0.15 0.17], ...
	'Tag','xAxis', ...
   'XColor',[0 0 0], ...
	'YColor',[0 0 0], ...
   'ZColor',[0 0 0]);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[0.494737 -0.324324 0], ...
	'Tag','xAxisXLabel', ...
	'VerticalAlignment','cap');
set(get(c,'Parent'),'XLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[-0.305263 0.486486 0], ...
	'Rotation',90, ...
	'Tag','xAxisYLabel', ...
	'VerticalAlignment','baseline');
set(get(c,'Parent'),'YLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','right', ...
	'Position',[-3.75789 1.98649 0], ...
	'Tag','xAxisZLabel', ...
	'Visible','off');
set(get(c,'Parent'),'ZLabel',c);
c = text('Parent',b, ...
   'Color',[0 0 0], ...
   'FontUnits','normalized', ...
   'FontSize',0.13, ...
   'FontWeight','bold', ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
   'Position',[0.494737 1.09459 0], ...
   'String','Input', ...
	'Tag','xAxisTitle', ...
	'VerticalAlignment','bottom');
set(get(c,'Parent'),'Title',c);
b = axes('Parent',a, ...
	'CameraUpVector',[0 1 0], ...
	'CameraUpVectorMode','manual', ...
	'Color',[1 1 1], ...
   'NextPlot','replacechildren', ...
	'Position',[0.83 0.73 0.15 0.17], ...
	'Tag','hAxis', ...
   'XColor',[0 0 0], ...
	'YColor',[0 0 0], ...
	'ZColor',[0 0 0]);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[0.489362 -0.338028 0], ...
	'Tag','hAxisXLabel', ...
	'VerticalAlignment','cap');
set(get(c,'Parent'),'XLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
	'Position',[-0.308511 0.478873 0], ...
	'Rotation',90, ...
	'Tag','hAxisYLabel', ...
	'VerticalAlignment','baseline');
set(get(c,'Parent'),'YLabel',c);
c = text('Parent',b, ...
	'Color',[0 0 0], ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','right', ...
	'Position',[-4.91489 2.04225 0], ...
	'Tag','hAxisZLabel', ...
	'Visible','off');
set(get(c,'Parent'),'ZLabel',c);
c = text('Parent',b, ...
   'Color',[0 0 0], ...
   'FontName','Helvetica', ...
   'FontUnits','normalized', ...
   'FontSize',0.13, ...
   'FontWeight','bold', ...
	'HandleVisibility','callback', ...
	'HorizontalAlignment','center', ...
   'Position',[0.489362 1.09859 0], ...
   'String','Impulse Response', ...
	'Tag','hAxisTitle', ...
	'VerticalAlignment','bottom');
set(get(c,'Parent'),'Title',c);
b = uicontrol('Parent',a, ...
   'Units','normalized', ...
   'BackgroundColor',[0.8 0.8 0.8], ...
   'CallBack','dconvdemo_callbacks TutorialButtonPush', ...
   'FontWeight','bold', ...
   'Position',[0.2150 0.1583 0.2 0.05], ...
   'String','Get Output', ...
   'Style','pushbutton', ...
   'Tag','TutorialButtonLinear', ...
   'Visible','off');
b = uicontrol('Parent',a, ...
   'Units','normalized', ...
   'BackgroundColor',[0.8 0.8 0.8], ...
   'CallBack','dconvdemo_callbacks TutorialButtonPush', ...
   'FontWeight','bold', ...
   'Position',[0.2150 0.1583 0.2 0.05], ...
   'String','Get Output', ...
   'Style','pushbutton', ...
   'Tag','TutorialButtonCircular', ...
   'Visible','off');
b = uicontrol('Parent',a, ...
	'Units','normalized', ...
	'BackgroundColor',[0.8 0.8 0.8], ...
   'Callback','dconvdemo_callbacks(get(gcbo,''String''))', ...
   'FontWeight','bold', ...
   'Position',[0.63 0.61 0.15 0.0613636], ...
   'String','Get x[n]', ...
	'Style','pushbutton', ...
	'Tag','GetButton');
b = uicontrol('Parent',a, ...
	'Units','normalized', ...
	'BackgroundColor',[0.8 0.8 0.8], ...
	'Callback','dconvdemo_callbacks(get(gcbo,''String''))', ...
   'FontWeight','bold', ...
	'Position',[0.83 0.61 0.15 0.0613636], ...
   'String','Get h[n]', ...
	'Style','pushbutton', ...
	'Tag','GetButton');
b = uicontrol('Parent',a, ...
	'Units','normalized', ...
	'BackgroundColor',[0.8 0.8 0.8], ...
   'Callback','dconvdemo_callbacks FlipButton', ...
	'FontWeight','bold', ...
	'Position',[0.66 0.55 0.1 0.037778], ...
	'String','Flip x[n]', ...
	'Style','radiobutton', ...
   'Tag','FlipButton', ...
   'Value',0);
b = uicontrol('Parent',a, ...
	'Units','normalized', ...
	'BackgroundColor',[0.8 0.8 0.8], ...
   'Callback','dconvdemo_callbacks FlipButton', ...
   'FontWeight','bold', ...
	'Position',[0.86 0.55 0.1 0.037778], ...
	'String','Flip h[n]', ...
	'Style','radiobutton', ...
	'Tag','FlipButton', ...
   'Value',1);
b = uicontrol('Parent',a, ...
   'Units','normalized', ...
   'Callback','dconvdemo_callbacks Close', ...
   'FontWeight','bold', ...
   'Position',[0.65 0.05 0.145 0.08], ...
   'String','Close', ...
   'Style','pushbutton', ...
   'Tag','CloseButton');
b = uicontrol('Parent',a, ...
   'Units','normalized', ...
   'Callback','dconvdemo_callbacks Help', ...
   'FontWeight','bold', ...
   'Position',[0.815 0.05 0.145 0.08], ...
   'String','Help', ...
   'Style','pushbutton', ...
   'Tag','HelpButton');