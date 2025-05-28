import { Component, OnInit } from '@angular/core';
import { Chart, plugins } from 'chart.js';
import { BaseChartDirective } from 'ng2-charts';

@Component({
  selector: 'app-line-chart',
  imports: [BaseChartDirective],
  templateUrl: './line-chart.component.html',
  styleUrls: ['./line-chart.component.scss'],
})
export class LineChartComponent {
  labels = ['Segunda-feira', 'Terça-feira', 'Quarta-feira', 'Quinta-feira', 'Sexta-feira', 'Sábado', 'Domingo'];

  cfg: any = {
    type: 'line',
    data: {
      labels: this.labels,
      datasets: [
        {
          color: '#fff',
          data: [10, 20, 30, 25, 21, 29, 40],
          label: 'Consumo em kWh',
        },
      ],
    },
    options: {
      plugins: {
        legend: {
          labels:{
            color: '#fff',
          }
        }
      },
      scales: {
        x:{
          grid: {
            color: '#888',
          },
        },
        y:{
          grid: {
            color: '#888',
          },
        }
      },
    },
  };
}
