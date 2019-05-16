# STOKES
<center>Polarization Spectrometer(PSIM) Data Processing Software<br></center>
<center>偏振光谱调制型(PSIM)偏振光谱仪数据处理软件</center>
##简介
###描述
<p>&#160; &#160; &#160; &#160; 该项目为使用PSIM技术光谱仪的数据处理程序。软件流程概括地来说可以包括光谱数据预处理、分通道解调、求Stokes矢量、计算偏振度这几个步骤。
<p>&#160; &#160; &#160; &#160; 光谱预处理主要包括将获得的光谱数据坐标变换，对坐标轴做倒数变换，从波长坐标变换到波数坐标，由于变换后的数据在波数坐标上并不均匀分布（原始的波长数据是几乎均匀变换的），所以要对其进行插值，从而获得分步均匀的值序列用于后续的处理，使用的插值过程是三次样条插值。
<p>&#160; &#160; &#160; &#160; 软件处理流程的起点是获得经过光谱仪获得的原始光谱，软件的输入除了包括实测光谱还包括一条预配置好的一组光谱：未调制的参考光谱、调制后的参考光谱，如上一节所述，获得的数据实际上是一个调制波形，所以首先要对其解调。而解调需要求出待解调的图像和用于解调的调制信号。所以这包括两个相对独立的过程：
<p>&#160; &#160; &#160; &#160; 求出待解调的图像：将实测光谱进行傅立叶变换，在变换后的频谱图像中，理论上可以找到包括0位置主峰在内的4个波峰，利用窗函数将4个波峰滤出，即分成4个通道的频谱图像。分别对4个通道的频谱进行反向傅立叶变换，得到4个通道的调制后图像。
<p>&#160; &#160; &#160; &#160; 求出调制信号：和对实测光谱进行处理的过程部分相似，这要利用预先测量好的参考光谱，首先对调制后的参考光谱，进行如上同样的步骤得到4个通道的调制后函数，将未加调制器测的的参考光谱进行同样的操作，得到4个通道未调制函数，将4个通道的调制、未调制函数点对点相除，从而求出调制系数。
<p>&#160; &#160; &#160; &#160; 有意思的是，调制和未调制的参考光谱都是预先配置好的（预先测量好的），所以可以说调制系数也是预置的。这里有个问题，在实际环境中，当环境因素变化时，调制器的仪器特性也会发生变化，调制系数会发生相应的变化，但这可以通过利用实测光谱计算进行调整，所以这个系统有“自校正”的特性，这将在下面详述。
<p>&#160; &#160; &#160; &#160; 现在得到了4个通道的实测调制函数和4个通道的调制系数，将他们点对点相除，将实测光谱解调得到MS0，MS1，MS2，MS3。其中可以利用通道0、1、2或0、2、3（高频部分）求出Stokes矢量，这里以通道0、1、2为例，记Stokes矢量为S0、S1、S2、S3，则S0 = MS0 ，S1 = MS1， S2 = MS2.real()， S3 = MS2.imag()，其中real()和imag()分别为取实部和虚部的运算。
<p>&#160; &#160; &#160; &#160; 然后通过以下公式可以求出偏振度函数：
<p>&#160; &#160; &#160; &#160; DOP = (S12 + S22 + S32)1/2  / S0
<p>&#160; &#160; &#160; &#160; 最后要解决一下当环境变化、实际调制系数发生变化时怎样进行自校正，这里需要计算两个相位角，记作α和β，可以利用下面的表达式对调制系数进行矫正。
<p>&#160; &#160; &#160; &#160; CS1 = CS1.rotate(α-β)
<p>&#160; &#160; &#160; &#160; CS2 = CS2.rotate(α)
<p>&#160; &#160; &#160; &#160; CS2 = CS2.rotate(α-β)
<p>&#160; &#160; &#160; &#160; 然后使用矫正后的调制系数重新计算Stokes矢量用于后续步骤，需要说明的是，目前实验环境下的数据有限，而实验室环境一般比较严格所以得到的幅角非常小，矫正后的调制系数也没有多大区别，所以尚不能明确这样的纠正是否能胜任实际情况下（大偏差时）的纠正。
 
### 图例
 
#### 偏振度幅图像(测量角度0度)

![0dop](https://github.com/ycroft/STOKES/blob/master/resources/imgs/0_dop.jpg "0 度")

#### 偏振度幅图像(测量角度15度)

![15dop](https://github.com/ycroft/STOKES/blob/master/resources/imgs/15_dop.jpg "15 度")

#### 偏振度幅图像(测量角度30度)

![30dop](https://github.com/ycroft/STOKES/blob/master/resources/imgs/30_dop.jpg "30 度")

#### 偏振度幅图像(测量角度45度)

![45dop](https://github.com/ycroft/STOKES/blob/master/resources/imgs/45_dop.jpg "45 度")

#### 偏振度幅图像(测量角度60度)

![60dop](https://github.com/ycroft/STOKES/blob/master/resources/imgs/60_dop.jpg "60 度")

### 作者

 &#160; &#160; &#160; &#160;[Yuhao Yin](http://www.ycroft.net)
 
 &#160; &#160; &#160; &#160;Fei Lin

