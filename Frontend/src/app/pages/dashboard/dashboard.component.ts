import { Component } from '@angular/core';
import { VisaoGeralComponent } from '../../components/visao-geral/visao-geral.component';
import { GraficoDonutComponent } from '../../components/grafico-donut/grafico-donut.component';
import { LineChartComponent } from '../../components/line-chart/line-chart.component';
import { HistoricoComponent } from '../../components/historico/historico.component';

@Component({
  selector: 'app-dashboard',
  imports: [VisaoGeralComponent, GraficoDonutComponent, LineChartComponent, HistoricoComponent],
  templateUrl: './dashboard.component.html',
  styleUrl: './dashboard.component.scss'
})
export class DashboardComponent {

}
