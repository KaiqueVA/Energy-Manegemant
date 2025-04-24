import { NgForOf } from '@angular/common';
import { Component } from '@angular/core';

@Component({
  selector: 'app-historico',
  imports: [NgForOf],
  templateUrl: './historico.component.html',
  styleUrl: './historico.component.scss'
})
export class HistoricoComponent {
  dadosConsumo: any[] = [
    { dia: '18/04', consumo: 12.5, valor: 8.75 },
    { dia: '19/04', consumo: 10.8, valor: 7.56 },
    { dia: '20/04', consumo: 11.3, valor: 7.91 },
    { dia: '21/04', consumo: 13.0, valor: 9.10 },
    { dia: '22/04', consumo: 9.7, valor: 6.79 },
    { dia: '23/04', consumo: 12.1, valor: 8.47 },
    { dia: '24/04', consumo: 11.6, valor: 8.12 },
  ];
}
