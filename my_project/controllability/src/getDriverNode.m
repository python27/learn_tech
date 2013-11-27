function nodes = getDriverNode(A)
% 给定任意一个网络的状态矩阵A,返回能够控制该网络的所有节点的集合
%
% 输入：网络的状态矩阵（一般为邻接矩阵的转置矩阵）
% 输出：控制该网络所需要的所有驱动节点集合
%
% 注意：节点的编号为1,2,...,N
%
% 算法来源：
% Paper: Exact controllbility of complex network
%        DOI: 10/1038/ncomms3447
%
% 作者：李新锋(lixinfeng@zju.edu.cn)
% 时间: 2013/11/21

    % 得到矩阵size，生成单位矩阵，计算驱动节点个数，及对应的特征值
    sizeA = size(A, 1);
    eyeMatrix = eye(sizeA);
    [nd, eigenvalue] = getDriverNodeNumber(A);
    
    % 计算中间矩阵 A - lambda * I
    ansMatrix = A - eigenvalue * eyeMatrix;
    
    % 进行列初等变换等价于计算转置矩阵的行初等变换
    rotateMatrix = rref(ansMatrix');
    independentIndex = zeros(1, sizeA);
    
    % 取得最大线性无关行向量所对应的index
    for i = 1:sizeA
        for j = i:sizeA
            if (rotateMatrix(i, j) ~= 0)
                independentIndex(j) = 1;
                break;
            end
        end
    end
    
    % 取补集，得到线性相关行所对应的index，即为驱动
    % 节点的index
    nodes = find(independentIndex == 0);   
end