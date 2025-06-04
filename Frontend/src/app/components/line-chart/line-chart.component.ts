import { Component, OnInit } from '@angular/core';
import { Chart, plugins } from 'chart.js';
import { BaseChartDirective } from 'ng2-charts';
import { MeasurementsService } from '../../services/measurements/measurements.service';

@Component({
  selector: 'app-line-chart',
  imports: [BaseChartDirective],
  templateUrl: './line-chart.component.html',
  styleUrls: ['./line-chart.component.scss'],
})
export class LineChartComponent {
  labels = ['Segunda-feira', 'Terça-feira', 'Quarta-feira', 'Quinta-feira', 'Sexta-feira', 'Sábado', 'Domingo'];
  consumo:any = [];
  constructor(private measurementService: MeasurementsService){}

  async ngOnInit(){
    this.consumo = (await this.measurementService.getWeek()).consumoPorDia;
    console.log(this.consumo);
  }

  cfg: any = {
    type: 'line',
    data: {
      labels: this.labels,
      datasets: [
        {
          color: '#fff',
          data: this.consumo,
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
