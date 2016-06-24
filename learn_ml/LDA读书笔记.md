#文本建模初步(UniGram模型, PLSA模型和LDA模型)
<center>作者: python27</center>
<center>日期: 2016/04/26</center>

##预备知识
###Gamma 函数
$$ \Gamma(x) = \int_{0}^{\infty} t^{x-1}e^{-t}dt $$
Gamma 函数的递归性质
$$ \Gamma(x+1) = x\Gamma(x) $$
Gamma 函数可以看作是阶乘在实数集上的延拓，具有如下性质：
$$ \Gamma(n) = (n-1)! $$

###Beta 分布
$$ f(x) = \frac{\Gamma(\alpha + \beta)}{\Gamma(\alpha)\Gamma(\beta)} x^{\alpha-1}(1-x)^{\beta-1} $$

###Beta-Binomial 共轭
$$Beta(p|\alpha, \beta) + BinomCount(m_1, m_2)=Beta(p|\alpha+m_1, \beta+m_2)$$
共轭的含义是当先验分布是Beta分布，样本数据是符合二项分布时，那么后验分布仍然是Beta分布，即具有形式上的不变性。

>这种形式不变的好处是，我们能够在先验分布中赋予参数明确的物理意义，这个物理意义可以延续到后验分布中进行解释，同时从先验变换到后验过程中从数据中补充的知识也容易有容易解释。

###Dirichlet 分布
####3维形式
$$f(x_1, x_2, x_3)=\frac{\Gamma(\alpha_1+\alpha_2+\alpha_3)}{\Gamma({\alpha_1})\Gamma({\alpha_2})\Gamma({\alpha_3})}x_1^{\alpha_1-1}x_2^{\alpha_2-1}x_3^{\alpha_3-1}$$

####一般形式
$$f(x_1, x_2,...,x_K)=\frac{\Gamma(\sum_{i=1}^{K}\alpha_i)}{\prod_{i=1}^{K}\Gamma(\alpha_i)}\prod_{i=1}^{K}x_i^{\alpha_i-1}$$

###Dirichlet-Multinomial 共轭
$$ Dir(\vec{p}|\vec{\alpha}) + Mult(\vec{m}) = Dir(\vec{p}|\vec{\alpha}+\vec{m}) $$

###Beta/Dirichlet分布的一个重要性质
如果 $p \sim Beta(t|\alpha, \beta) $, 则 $E(p) = \frac{\alpha}{\alpha+\beta}$

如果 $\vec{p} \sim Dir(\vec{t}|\vec{\alpha})$, 则 $E(\vec{p})= (\frac{\alpha_1}{\sum_{i=1}^{K}\alpha_i}, \frac{\alpha_2}{\sum_{i=1}^{K}\alpha_i}, \ldots, \frac{\alpha_K}{\sum_{i=1}^{K}\alpha_i})$

### Metropolis-Hastings采样算法

1. 初始化马尔科夫链初始状态 $X_0=x_0$
2. 对$t=0,1,2,\ldots$，循环以下过程采样
  - 第t时刻马尔科夫链状态为$X_t=x_t$，采样$y\sim q(x|x_t)$
  - 从均匀分布采样 $u \sim U(0, 1)$
  - 如果 $u < \alpha(x_t, y) = min{\frac{p(y)q(x_t|y)}{p(x_t)p(y|x_t)}, 1}$,则接受转移 $x_t \rightarrow y$，即$X_{t+1}=y$
  - 否则，不接受转移, 即 $X_{t+1}=x_t$

### 二维Gibbs Sampling算法
1. 随机初始化 $X_0=x_0$, $Y_0 = y_0$
2. 对于$t=0, 1, 2, \ldots$循环采样
  - $y_{t+1} \sim p(y|x_t)$
  - $x_{t+1} \sim p(x|y_{t+1})$

## 文本建模

### UniGram Model
假设词典中一共有$V$个词$v_1, v_2, ..., v_N$, UniGram模型假设认为文档按照下列规则产生:

1. 上帝只有一个骰子， 这个骰子有$V$个面，每个面对应一个词，各面概率不同；
2. 每次投掷骰子一次，抛出的一个面，产生一个对应的词；如果文档有 $n$ 个词，仅需要投掷骰子$n$次即可。

记骰子各面的概率为$\vec{p} = (p_1, p_2, ..., p_V)$, 则每次投掷骰子相当于是抛硬币的伯努利实验的推广（这里硬币有多个面），不妨记 $w \sim Mult(w|\vec{p})$

如此，对于一篇文档$d=\vec{w}=(w_1, w_2, ..., w_n)$，该文档被生成的概率是 $$p(\vec{w})=p(w_1, w_2, ..., w_n)=p(w_1)p(w_2)...p(w_n)$$
多篇文档之间认为是相互独立的，这样语料库$W=(\vec{w_1}, \vec{w_2},...,\vec{w_m})$的概率为
$$P(W) = p(\vec{w_1})p(\vec{w_2})...p(\vec{w_m})$$

>这里假设文档之间是独立可交换的，同时文档中的单词也是独立可交换的，所以一篇文档相当于一个袋子，里面装了一些词，而词的顺序信息也无关紧要，这样的模型称为**词袋模型(Bag of words)**

假设在料库中，共有$N$个单词，其中每个单词$w_i$出现的次数为$n_i$,则整个语料库出现的概率为
$$
P(W) = p(\vec{w_1})p(\vec{w_2})...p(\vec{w_m})=p(w_{11})p(w_{12})...p(w_{1m_1})p(w_{21})p(w_{22})...p(w_{2m_2})...p(w_{m1})p(w_{m2})...p(w_{mm_1})= p_1^{n_1}p_2^{n_2}...p_V^{n_V}=\prod_{k=1}^{V}p_k^{n_k}
$$
参数估计，使用最大似然估计最大化$P(W)$，得到
$$\hat{p_i}^ = \frac{n_i}{N}$$

### 贝叶斯Unigram Model
之前的Unigram Model认为模型参数是固定，只是上帝知道我们不知道；而贝叶斯Unigram Model认为模型的参数本身也是一个随机变量，服从一定的概率分布，这样贝叶斯Unigram Model的规则为：

1. 上帝有一个坛子，里面装有无数个骰子，每个骰子有V个面；
2. 上帝随机从坛子中挑选一个骰子，然后不断投掷，直到产生语料库中的所有词。

假设里面的骰子参数$\vec{p}$服从概率分布$p(\vec{p})$，这个分布称为参数$\vec{p}$的先验分布。

很明显，对于一个骰子参数$\vec{p}$，预料产生的概率为$P(W|\vec{p})$，所以根据全概率公式，则整个语料库产生的概率为：

$$P(W)=\int P(W|\vec{p})p(\vec{p})d{\vec{p}}$$

在先验概率$p(\vec{p})$已知的情况下， 有前面$P(W)$的概率取决于单词库的单词在语料库中出现的频数向量$\vec{n}=(n_1, n_2, ..., n_V)$.

假设在料库中，共有$N$个单词，其中每个单词$w_i$出现的次数为$n_i$, 那么$\vec{n}=(n_1, n_2, ..., n_V)$出现的概率为：
$$p(\vec{n})=Mult(\vec{n}|\vec{p}, N)=\binom{N}{\vec{n}}\prod_{k=1}^{N}p_k^{n_k}$$

由于$\vec{n}$服从于多项分布，根据前面的Dirichlet-Multinomial 共轭知识，如果选择先验分布$p(\vec{p})$服从Dirichlet分布，那么后验分布也将服从于Dirichlet分布。

所以假设先验为Dirichlet分布，即
$$Dir(\vec{p}|\vec{\alpha})=\frac{1}{\Delta(\vec{\alpha})}\prod_{k=1}^{V}p_k^{\alpha_k-1}$$
其中$\vec{\alpha}=(\alpha_1, ..., \alpha_V)$, $\Delta(\vec{\alpha})$是归一化因子, 即
$$\Delta(\vec{\alpha})=\int \prod_{k=1}^{V}p_k^{\alpha_k-1}d\vec{p}$$

根据前面的Dirichlet-Multinomial 共轭，不需要计算我们就知道后验分布为
$$
p(\vec{p}|W, \vec{\alpha})=Dir(\vec{p}|\vec{n}+\vec{\alpha})=\frac{1}{\Delta(\vec{n}+\vec{\alpha})}\prod_{k=1}^{V}p_k^{n_k+\alpha_k-1}d\vec{p}
$$

#### 参数$\vec{p}$的估计
由于我们已经知道了后验分布，所以可以使用均值进行估计，可以用之前关于Dirichlet分布的重要性质得到，如果 $\vec{p} \sim Dir(\vec{p}|\vec{n}+\vec{\alpha})$, 则
$$E(\vec{p})=\left(\frac{n_1+\alpha_1}{\sum_{i=1}^{V}(n_i+\alpha_i)}, \frac{n_2+\alpha_2}{\sum_{i=1}^{V}(n_i+\alpha_i)}, \ldots, \frac{n_V+\alpha_V}{\sum_{i=1}^{V}(n_i+\alpha_i)} \right)$$
即对于每个分量$p_i$，我们的估计值为
$$\hat{p_i}=\frac{n_i+\alpha_i}{\sum_{i=1}^{V}(n_i+\alpha_i)}$$

####物理意义解释
>考虑到$\alpha_i$在Dirichlet分布中表示事件的先验伪计数，这个估计的含义是：每个参数的估计值使其对应事件的先验伪计数和数据的计数和在整个计数中所占的比例.

####语料库产生的概率为
$$P(W|\vec{\alpha})=\frac{\Delta(\vec{n}+\vec{\alpha})}{\Delta(\alpha)}$$

## PLSA(Probabilistic Latent Semantic Analysis) Topic Model
