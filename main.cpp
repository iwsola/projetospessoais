#include "mainwindow.h"
#include <QMainWindow>
#include <bits/stdc++.h>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QTimer>
#include <QStatusBar>
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{

    long long auraFarmada = 1;


    QApplication app(argc, argv);
    double time = 1000;
    double auraInterval = (time/1000);
    double auraInit = 1;
    double auraTaxa = auraInit/auraInterval;
    long long custo = 100;
    long long custoHit = 100;
    int contador = 1;
    int contador2 = 1;
    double onhitTAX = 1;




    QMainWindow janela1;
        janela1.setWindowTitle("Farmador de Aura");
        janela1.resize(1200,750);
        janela1.setMinimumSize(900,450);

    QWidget *widgetCentral = new QWidget();
        janela1.setCentralWidget(widgetCentral);

    QVBoxLayout *layout = new QVBoxLayout(widgetCentral);
        layout->setSpacing(30);
        layout->setContentsMargins(40, 40, 40, 40);

        QLabel *aura = new QLabel();
        QPixmap aurudo(":/aura.png");
        aura -> setPixmap(aurudo.scaled(350,350, Qt::KeepAspectRatio));
        aura -> setAlignment(Qt::AlignCenter);
        QLabel *mensagem = new QLabel("Farme aura como Thiago Galhardo!");
        QLabel *nome = new QLabel("AURA!");
        nome -> setAlignment(Qt::AlignCenter);
        mensagem -> setAlignment(Qt::AlignCenter);
        QLabel *taxaAura = new  QLabel(QString("Aura farmada por segundo: %1/s").arg(QString::number(auraTaxa, 'f', 2)));
        QPushButton *botaoAura = new QPushButton("Clique para aumentar sua aura!");
        botaoAura -> setCursor(Qt::PointingHandCursor);
        QPushButton *botaoLoja = new QPushButton("Loja");
        botaoLoja -> setCursor(Qt::PointingHandCursor);


    QMainWindow loja1;
        loja1.setWindowTitle("Loja da Aura");
        loja1.resize(800,800);
        loja1.setMinimumSize(400,600);

    QWidget *widgetLoja = new QWidget();
        loja1.setMenuWidget(widgetLoja);

    QVBoxLayout *layoutLoja = new QVBoxLayout(widgetLoja);
        layoutLoja->setSpacing(30);
        layoutLoja->setContentsMargins(40, 40, 40, 40);

        QLabel *custo1 = new QLabel(QString("Custo do upgrade passivo: %1").arg(QString::number(custo,'f',2)));
        QLabel *nomeLoja = new QLabel("Gaste aura para farmar mais AURA AINDA!");
        QLabel *custo2 = new QLabel(QString("Custo do upgrade on-hit: %1").arg(QString::number(custoHit,'f',2)));
        QPushButton *botaoLOJA1 = new QPushButton("Aumentar aura farmada passivamente");
        QPushButton *botaoLOJA2 = new QPushButton("Aumentar aura farmada on-hit");

        layoutLoja->addWidget(nomeLoja);
        layoutLoja->addWidget(botaoLOJA1);
        layoutLoja->addWidget(custo1);
        layoutLoja->addWidget(botaoLOJA2);
        layoutLoja->addWidget(custo2);

            QObject::connect(botaoLOJA1, &QPushButton::clicked,[&](){

                    auraTaxa = auraTaxa + 2;
                    auraFarmada = auraFarmada - custo;
                    contador++;
                    custo = 100*contador;
                    custo1 -> setText(QString("Custo do upgrade passivo: %1").arg(QString::number(custo,'f',2)));
                    taxaAura -> setText(QString("Aura farmada por segundo: %1/s").arg(QString::number(auraTaxa, 'f', 2)));
            });

         QObject::connect(botaoLOJA2, &QPushButton::clicked,[&](){

                onhitTAX += onhitTAX *1.5;
                auraFarmada = auraFarmada - custoHit;
                contador2 += contador2*1.7;
                custoHit = 100*contador2;
                custo2-> setText(QString("Custo do upgrade on-hit: %1").arg(QString::number(custoHit,'f',2)));
            });



    layout -> addWidget(mensagem);
    layout -> addWidget(nome);
    layout -> addWidget(aura);
    layout -> addWidget(botaoAura);
    layout -> addWidget(botaoLoja);
    layout -> addStretch();
    janela1.statusBar() -> addPermanentWidget(taxaAura);

    auto checkLoja = [&](){
        if(auraFarmada >= custo)
        {
            botaoLOJA1 -> setEnabled(true);
        }
        else
        {
            botaoLOJA1 -> setEnabled(false);
        }

        if(auraFarmada >= custoHit)
        {
            botaoLOJA2 -> setEnabled(true);
        }
        else
        {
            botaoLOJA2 -> setEnabled(false);
        }
    };

    auto atualizarQtd = [&]() {
            nome->setText(QString("Aura farmada: %1").arg(auraFarmada));
     };

    auto check = [&]()
    {
        if((auraFarmada % 100) == 0)
        {
            janela1.statusBar()->showMessage("Atingiu um novo marco!", 3000);
        }
    };

    QObject::connect(botaoLoja, &QPushButton::clicked,[&]()
    {
        loja1.show();

        checkLoja();
    });

    QObject::connect(botaoAura, &QPushButton::clicked,[&]()
    {
        auraFarmada = auraFarmada + onhitTAX;
        atualizarQtd();
        check();

        checkLoja();
    });

    QTimer *timer = new QTimer(&janela1);
    QObject::connect(timer, &QTimer::timeout, [&]()
    {
        auraFarmada = auraFarmada + auraTaxa;
        atualizarQtd();
        check();

        checkLoja();
    });

    timer->start(time);


    janela1.show();

    return app.exec();
}
