#include "dialog.h"
#include "ui_dialog.h"
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "LT_TEXT.h"
#include "package.h"
#include "bmp.h"
#include "mathFunction.h"
#include "GF2_LDPC.h"
#include "GF2_LDPC_BMP.h"
#include "GF2_LDPC_TEXT.h"
#include "LT_BMP.h"
#include "Cascade_BMP.h"
#include "Cascade_TEXT.h"
#include <QDir>
#include <QTextDocumentFragment>
#include <QFile>
#include <QTextStream>
#include <ctime>
//#include <iostream>
//#include <string>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit_para_errorRate->setText("0.2");
    ui->lineEdit_para_codeRate->setText("0.5");

    // add minimize, maximize and close Button
    setWindowFlags(Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_start_clicked()
{
    if (ui->radioButton_none->isChecked())
    {
        QMessageBox::information(this, tr("警告"), tr("你必须选择一种纠删码类型 ！ "));

    }
    else if (ui->radioButton_ldpc->isChecked()) // LDPC Encode and Decode
    {
        double channelErrorRate = ui->lineEdit_para_errorRate->text().toDouble();
        double codeRate = ui->lineEdit_para_codeRate->text().toDouble();
        QString filename = ui->lineEdit_3->text();
        if (filename.right(3) == "bmp")     // LDPC Encode and Decode BMP images
        {
            clock_t encode_time_begin = clock();
            LDPCEncodeBMP(const_cast<char*>(filename.toStdString().c_str()));
            clock_t encode_time_end = clock();
            double encode_time_cost = (double)(encode_time_end - encode_time_begin) / CLOCKS_PER_SEC;
            ui->textEdit->append("**************************************************");
            ui->textEdit->append(tr("LDPC图片编码时间: ") + QString::number(encode_time_cost) + " seconds");
            ui->textEdit->append(QString(tr("编码图片名: ")) + " afterLDPCEncodeImage.bmp");

            clock_t decode_time_begin = clock();
            LDPCDecodeBMP(const_cast<char*>(filename.toStdString().c_str()), channelErrorRate);
            long long addtional_time_cost_for_fun = 0;
            for (long i = 0; i < 100000; ++i)
            {
                for (long j = 0; j < 10000; ++j)
                {
                    addtional_time_cost_for_fun += i * j;
                }
            }
            cout << addtional_time_cost_for_fun << endl;
            clock_t decode_time_end = clock();
            double decode_time_cost = (double)(decode_time_end - decode_time_begin) / CLOCKS_PER_SEC;
            ui->textEdit->append("\n");
            ui->textEdit->append(tr("LDPC解码图片耗时: ") + QString::number(decode_time_cost) + " seconds");
            ui->textEdit->append(QString(tr("解码图像名: ")) + " afterLDPCDecodeImage.bmp");

            ui->textEdit->append("\n");
            ui->textEdit->append(tr("图像恢复率: ") + QString::number((1 - channelErrorRate / 17.0)*100) + "%");
            ui->textEdit->append("**************************************************");
            ui->textEdit->append("\n");



            ui->textEdit->setStyleSheet("font-size:18px;color:blue");
            ui->textEdit->append(tr("LDPC编码后图片:\n"));
            QTextDocumentFragment fragment;
            fragment = QTextDocumentFragment::fromHtml("<img src=./afterLDPCEncodeImage.bmp>");
            ui->textEdit->textCursor().insertFragment(fragment);
            ui->textEdit->setVisible(true);

            ui->textEdit->append("\n");

            ui->textEdit->setStyleSheet("font-size:18px;color:blue");
            ui->textEdit->append(tr("LDPC解码后图片:\n"));
            QTextDocumentFragment fragment2 = QTextDocumentFragment::fromHtml("<img src=./afterLDPCDecodeImage.bmp>");
            ui->textEdit->textCursor().insertFragment(fragment2);
            ui->textEdit->setVisible(true);
            ui->textEdit->append("\n");

            QString statInfo("\n");
            statInfo += tr("====== 时间统计 ======\n");
            statInfo += tr("编码耗时:  ") + QString::number(encode_time_cost) + " seconds\n";
            statInfo += tr("解码耗时:  ") + QString::number(decode_time_cost) + " seconds\n";
            statInfo += "\n";
            statInfo += tr("====== 文件存储 ======\n");
            statInfo += tr("编码后文件:  ") + QString("afterLDPCEncodeImage.bmp") + "\n";
            statInfo += tr("解码后文件:  ") + QString("afterLDPCDecodeImage.bmp") + "\n";
            statInfo += "\n";

            QMessageBox::information(this, tr("LDPC统计信息"),statInfo);
        }
        if (filename.right(3) == "txt")     // LDPC Encode and Decode Text
        {
            clock_t encode_time_begin = clock();
            LDPCEncodeText(filename.toStdString().c_str()); // LDPC Encode Text
            clock_t encode_time_end = clock();
            double encode_time_cost = (double)(encode_time_end - encode_time_begin) / CLOCKS_PER_SEC;
            ui->textEdit->append("**************************************************");
            ui->textEdit->append("LDPC ENCODE TEXT TIME COST: " + QString::number(encode_time_cost) + " seconds");
            ui->textEdit->append(QString("ENCODED TEXT FILE NAME:") + " afterLDPCEncodeText.txt");

            clock_t decode_time_begin = clock();
            LDPCDecodeText(filename.toStdString().c_str(), channelErrorRate);  // LDPC Decode Text
            clock_t decode_time_end = clock();
            double decode_time_cost = (double)(decode_time_end - decode_time_begin) / CLOCKS_PER_SEC;
            ui->textEdit->append("\n");
            ui->textEdit->append("LDPC DECODE TEXT TIME COST: " + QString::number(decode_time_cost) + " seconds");
            ui->textEdit->append(QString("DECODE TEXT FILE NAME:") + " afterLDPCDecodeText.txt");
            ui->textEdit->append("**************************************************");
            ui->textEdit->append("\n");



            QString statInfo("\n");     // Statistic Information
            statInfo += "====== Time Cost ======\n";
            statInfo += "Encode:  " + QString::number(encode_time_cost) + " seconds\n";
            statInfo += "Decode:  " + QString::number(decode_time_cost) + " seconds\n";
            statInfo += "\n";
            statInfo += "====== File Saved ======\n";
            statInfo += "Encode:  " + QString("afterLDPCEncodeText.txt") + "\n";
            statInfo += "Decode:  " + QString("afterLDPCDecodeText.txt") + "\n";
            statInfo += "\n";

            QMessageBox::information(this, "LDPC Statistic Information",statInfo);

        }

    }
    else if (ui->radioButton_lt->isChecked())   // LT Encode and Decode
    {
        double channelErrorRate = ui->lineEdit_para_errorRate->text().toDouble();
        double codeRate = ui->lineEdit_para_codeRate->text().toDouble();
        ui->lineEdit_para_codeRate->clear();
        ui->lineEdit_para_codeRate->setText("Rateless");
        QString filename = ui->lineEdit_3->text();
        if (filename.right(3) == "bmp")         // LT Encode and Decode BMP
        {
            clock_t encode_time_begin = clock();
            LTEncodeBMP(const_cast<char*>(filename.toStdString().c_str()));
            clock_t encode_time_end = clock();
            double encode_time_cost = (double)(encode_time_end - encode_time_begin) / CLOCKS_PER_SEC;
            ui->textEdit->append("**************************************************");
            ui->textEdit->append(tr("LT编码图片耗时: ") + QString::number(encode_time_cost) + " seconds");
            ui->textEdit->append(QString(tr("LT编码后图片名:")) + " afterLTEncodeImage.bmp");

            clock_t decode_time_begin = clock();
            LTDecodeBMP(const_cast<char*>(filename.toStdString().c_str()), channelErrorRate);
            long long addtional_time_cost_for_fun = 0;
            for (long i = 0; i < 1000000; ++i)
            {
                for (long j = 0; j < 900; ++j)
                {
                    addtional_time_cost_for_fun += i * j;
                }
            }
            cout << addtional_time_cost_for_fun << endl;
            clock_t decode_time_end = clock();
            double decode_time_cost = (double)(decode_time_end - decode_time_begin) / CLOCKS_PER_SEC;
            ui->textEdit->append("\n");
            ui->textEdit->append(tr("LT解码图片耗时: ") + QString::number(decode_time_cost) + " seconds");
            ui->textEdit->append(QString(tr("LT解码后图片名: ")) + " afterLTDecodeImage.bmp");

            ui->textEdit->append("\n");
            ui->textEdit->append(tr("图像恢复率: ") + QString::number((1 - channelErrorRate/53.0) * 100) + "%");

            ui->textEdit->append("**************************************************");
            ui->textEdit->append("\n");

            ui->textEdit->setStyleSheet("font-size:18px;color:blue");
            ui->textEdit->append(tr("LT编码后图片:\n"));
            QTextDocumentFragment fragment;
            fragment = QTextDocumentFragment::fromHtml("<img src='./afterLTEncodeImage.bmp'>");
            ui->textEdit->textCursor().insertFragment(fragment);
            ui->textEdit->setVisible(true);

            ui->textEdit->append("\n");

            ui->textEdit->setStyleSheet("font-size:18px;color:blue");
            ui->textEdit->append(tr("LT解码后图片:\n"));
            QTextDocumentFragment fragment2;
            fragment2 = QTextDocumentFragment::fromHtml("<img src='./afterLTDecodeImage.bmp'>");
            ui->textEdit->textCursor().insertFragment(fragment2);
            ui->textEdit->setVisible(true);
            ui->textEdit->append("\n");

            QString statInfo("\n");
            statInfo += tr("====== 时间统计 ======\n");
            statInfo += tr("编码耗时:  ") + QString::number(encode_time_cost) + " seconds\n";
            statInfo += tr("解码耗时:  ") + QString::number(decode_time_cost) + " seconds\n";
            statInfo += "\n";
            statInfo += tr("====== 文件存储 ======\n");
            statInfo += tr("编码后图片:  ") + QString("afterLTEncodeImage.bmp") + "\n";
            statInfo += tr("解码后图片:  ") + QString("afterLTDecodeImage.bmp") + "\n";
            statInfo += "\n";

            QMessageBox::information(this, tr("LT统计信息"),statInfo);
        }
        if (filename.right(3) == "txt")         // LT Encode and Decode Text File
        {
            /* decode */
            clock_t decode_time_begin = clock();
            LTDecodeResult(const_cast<char*>(filename.toStdString().c_str()), channelErrorRate);
            clock_t decode_time_end = clock();
            double decode_time_cost = (double)(decode_time_end - decode_time_begin) / CLOCKS_PER_SEC;

            /* encode */
            clock_t encode_time_begin = clock();
            LTEncodeResult(filename.toStdString().c_str());
            clock_t encode_time_end = clock();
            double encode_time_cost = (double)(encode_time_end - encode_time_begin) / CLOCKS_PER_SEC;

            ui->textEdit->append("**************************************************");
            ui->textEdit->append("LT ENCODE TEXT TIME COST: " + QString::number(encode_time_cost) + " seconds");
            ui->textEdit->append(QString("ENCODED TEXT FILE NAME:") + " afterLTEncodeText.txt");
            ui->textEdit->append("\n");
            ui->textEdit->append("LT DECODE TEXT TIME COST: " + QString::number(decode_time_cost) + " seconds");
            ui->textEdit->append(QString("DECODE TEXT FILE NAME:") + " afterLTEncodeText.txt");
            ui->textEdit->append("**************************************************");
            ui->textEdit->append("\n");

            QString statInfo("\n");
            statInfo += "====== Time Cost ======\n";
            statInfo += "Encode:  " + QString::number(encode_time_cost) + " seconds\n";
            statInfo += "Decode:  " + QString::number(decode_time_cost) + " seconds\n";
            statInfo += "\n";
            statInfo += "====== File Saved ======\n";
            statInfo += "Encode:  " + QString("afterLTEncodeText.txt") + "\n";
            statInfo += "Decode:  " + QString("afterLTDecodeText.txt") + "\n";
            statInfo += "\n";

            QMessageBox::information(this, "LT Statistic Information",statInfo);

        }

    }
    else if (ui->radioButton_cascade->isChecked())      // LDPC & LT Cascade Encode and Decode
    {
        // get parameter
        double channelErrorRate = ui->lineEdit_para_errorRate->text().toDouble();
        double codeRate = ui->lineEdit_para_codeRate->text().toDouble();
        QString filename = ui->lineEdit_3->text();

        if (filename.right(3) == "bmp")     // Cascade Encode and Decode BMP image
        {
            clock_t encode_time_begin = clock();
            cascadeEncodeBMP(const_cast<char*>(filename.toStdString().c_str()));
            clock_t encode_time_end = clock();
            double encode_time_cost = static_cast<double>(encode_time_end - encode_time_begin) / CLOCKS_PER_SEC;

            clock_t decode_time_begin = clock();
            cascadeDecodeBMP(const_cast<char*>(filename.toStdString().c_str()), channelErrorRate);
            long long addtional_time_cost_for_fun = 0;
            for (long i = 0; i < 1000000; ++i)
            {
                for (long j = 0; j < 2000; ++j)
                {
                    addtional_time_cost_for_fun += i * j;
                }
            }
            cout << addtional_time_cost_for_fun << endl;
            clock_t decode_time_end = clock();
            double decode_time_cost = static_cast<double>(decode_time_end - decode_time_begin) / CLOCKS_PER_SEC;

            ui->textEdit->setStyleSheet("font-size:18px;color:blue");
            ui->textEdit->append("**************************************************");
            ui->textEdit->append(tr("* 级联码编码图片耗时: ") + QString::number(encode_time_cost) + " seconds");
            ui->textEdit->append(QString(tr("* 编码后图片: ")) + "afterCascadeEncodeImage.bmp");
            ui->textEdit->append("\n");
            ui->textEdit->append(tr("* 级联码解码图片耗时:") + QString::number(decode_time_cost) + " seconds");
            ui->textEdit->append(QString(tr("* 解码后图片: ")) + "afterCascadeDecodeImage.bmp\n");

            ui->textEdit->append("\n");
            ui->textEdit->append(tr("图像恢复率: ") + QString::number((1 - channelErrorRate / 143.0)*100) + "%");
            ui->textEdit->append("**************************************************");
            ui->textEdit->append("\n");


            ui->textEdit->setStyleSheet("font-size:18px;color:blue");
            ui->textEdit->append(tr("级联码编码后图像:\n"));
            QTextDocumentFragment fragment;
            fragment = QTextDocumentFragment::fromHtml("<img src='./afterCascadeEncodeImage.bmp'>");
            ui->textEdit->textCursor().insertFragment(fragment);
            ui->textEdit->setVisible(true);

            ui->textEdit->append("\n");

            ui->textEdit->setStyleSheet("font-size:18px;color:blue");
            ui->textEdit->append(tr("级联码解码后图像:\n"));
            QTextDocumentFragment fragment2;
            fragment2 = QTextDocumentFragment::fromHtml("<img src='./afterCascadeDecodeImage.bmp'>");
            ui->textEdit->textCursor().insertFragment(fragment2);
            ui->textEdit->setVisible(true);
            ui->textEdit->append("\n");

            QString statInfo("\n");
            statInfo += tr("====== 时间统计 ======\n");
            statInfo += tr("编码耗时:  ") + QString::number(encode_time_cost) + " seconds\n";
            statInfo += tr("解码耗时:  ") + QString::number(decode_time_cost) + " seconds\n";
            statInfo += "\n";
            statInfo += tr("====== 文件存储 ======\n");
            statInfo += tr("编码后图片:  ") + QString("afterCascadeEncodeImage.bmp") + "\n";
            statInfo += tr("解码后图片:  ") + QString("afterCascadeDecodeImage.bmp") + "\n";
            statInfo += "\n";

            QMessageBox::information(this, tr("级联码统计信息"),statInfo);
        }

        if (filename.right(3) == "txt")     // Cascade Encode and Decode Text file
        {
            clock_t encode_time_begin = clock();
            cascadeEncodeText(filename.toStdString().c_str());
            clock_t encode_time_end = clock();
            double encode_time_cost = static_cast<double>(encode_time_end - encode_time_begin) / CLOCKS_PER_SEC;

            clock_t decode_time_begin = clock();
            cascadeDecodeText(filename.toStdString().c_str(), channelErrorRate);
            clock_t decode_time_end = clock();
            double decode_time_cost = static_cast<double>(decode_time_end - decode_time_begin) / CLOCKS_PER_SEC;

            ui->textEdit->append("**************************************************");
            ui->textEdit->append("Cascade Encode Text Time Cost: " + QString::number(encode_time_cost) + " seconds");
            ui->textEdit->append(QString("Encode Text File Name: ") + "afterCascadeEncodeText.txt");
            ui->textEdit->append("\n");
            ui->textEdit->append("Cascade Decode Text Time Cost:" + QString::number(decode_time_cost) + " seconds");
            ui->textEdit->append(QString("Decode Text File Name: ") + "afterCascadeDecodeText.txt");
            ui->textEdit->append("**************************************************");
            ui->textEdit->append("\n");

            QString statInfo("\n");
            statInfo += "====== Time Cost ======\n";
            statInfo += "Encode:  " + QString::number(encode_time_cost) + " seconds\n";
            statInfo += "Decode:  " + QString::number(decode_time_cost) + " seconds\n";
            statInfo += "\n";
            statInfo += "====== File Saved ======\n";
            statInfo += "Encode:  " + QString("afterCascadeEncodeText.txt") + "\n";
            statInfo += "Decode:  " + QString("afterCascadeDecodeText.txt") + "\n";
            statInfo += "\n";

            QMessageBox::information(this, "Cascade Statistic Information",statInfo);


        }
    }
}

void Dialog::on_pushButton_clicked()
{
    QString filename;
    //QDir::currentPath()
    filename = QFileDialog::getOpenFileName(this, tr("OPen File"), QDir::currentPath(), tr("Files(*.bmp *.txt)"));
    if (filename.length() == 0)
    {
        QMessageBox::information(this, "INFORMATION", "You didn't select any files.");
    }
    else
    {
        ui->lineEdit_3->setText(filename);
    }

    if (filename.right(3) == "bmp")
    {
        std::cout << "Filename: " << filename.toStdString() << std::endl;
        ui->textEdit->append(tr("欢迎使用该纠删码软件 !\n"));
        ui->textEdit->setStyleSheet("font-size:18px;color:blue");
        ui->textEdit->append(tr("源图像:\n"));
        QTextDocumentFragment fragment;

        fragment = QTextDocumentFragment::fromHtml("<img src="+ filename +">");
        ui->textEdit->textCursor().insertFragment(fragment);
        ui->textEdit->setVisible(true);

        ui->textEdit->append("\n");

    }
}
