import { Component } from '@angular/core';
import { VisaoGeralComponent } from '../../components/visao-geral/visao-geral.component';
import { GraficoDonutComponent } from '../../components/grafico-donut/grafico-donut.component';
import { LineChartComponent } from '../../components/line-chart/line-chart.component';
import { HistoricoComponent } from '../../components/historico/historico.component';
import { SwitchTomadaComponent } from '../../components/switch-tomada/switch-tomada.component';
import { Router } from '@angular/router';
import { ApiService } from '../../services/api/api.service';
import { FormsModule } from '@angular/forms';
import { MeasurementsService } from '../../services/measurements/measurements.service';

@Component({
  selector: 'app-dashboard',
  imports: [
    VisaoGeralComponent,
    GraficoDonutComponent,
    LineChartComponent,
    HistoricoComponent,
    SwitchTomadaComponent,
    FormsModule,
  ],
  templateUrl: './dashboard.component.html',
  styleUrl: './dashboard.component.scss',
})
export class DashboardComponent {
  username = sessionStorage.getItem('name');
  meuValor = false;
  tarifa = 3;

  constructor(private router: Router, private measurementService : MeasurementsService) {}

  async ngOnInit() {
    this.measurementService.getSevenDays();
  }

  

  logout() {
    sessionStorage.clear();
    this.router.navigate(['']);
  }
}
