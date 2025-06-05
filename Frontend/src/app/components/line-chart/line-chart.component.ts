import { Component, OnInit, ViewChild } from '@angular/core';
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
  consumo_dia: any = [];
  @ViewChild(BaseChartDirective) chart: BaseChartDirective | undefined;


  constructor(private measurementService: MeasurementsService){}

  async ngOnInit(){
    this.consumo = (await this.measurementService.getWeek());
    console.log(this.consumo);
    this.consumo.map((e:any) => {
      this.consumo_dia.push(e.kwh);
    })

    this.cfg.data.datasets[0].data = this.consumo_dia;

    this.chart?.update();
  }

  cfg: any = {
    type: 'line',
    data: {
      labels: this.labels,
      datasets: [
        {
          color: '#fff',
          data: [],
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
