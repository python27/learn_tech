function [ND, eigenvalue] = getDriverNodeNumber(A)
% 给定任意一个网络的状态矩阵A，计算完全控制该网络所需要的驱动节点的个数
%
% 输入：网络的状态矩阵A（一般为邻接矩阵的转置矩阵）
% 输出：1. 控制该网络所要的最少驱动节点的个数
%       2. 对应的特征值
% 
% 注意：节点的编号为1,2,3,...,N
%
% 算法来源：
% Paper: Exact controllbility of complex network
%        DOI: 10/1038/ncomms3447
%
% 作者：李新锋 (lixinfeng@zju.edu.cn)
% 时间：2013/11/21

N = size(A, 1);

% 计算特征值
d = eig(A);
% 获取单位矩阵
e = eye(N);

ND = -1;
dsize = size(d, 1);

% 计算所有可能的u(\lambda) 找到其中最大的
for i = 1:dsize
    curAns = N - rank(d(i) * e - A);
    if (curAns > ND)
        ND = curAns;
        eigenvalue = d(i);
    end
end

end