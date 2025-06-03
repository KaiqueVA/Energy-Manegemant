import { Component } from '@angular/core';
import { VisaoGeralComponent } from '../../components/visao-geral/visao-geral.component';
import { GraficoDonutComponent } from '../../components/grafico-donut/grafico-donut.component';
import { LineChartComponent } from '../../components/line-chart/line-chart.component';
import { HistoricoComponent } from '../../components/historico/historico.component';
import { SwitchTomadaComponent } from '../../components/switch-tomada/switch-tomada.component';
import { Router } from '@angular/router';
import { ApiService } from '../../services/api/api.service';
import { FormsModule } from '@angular/forms';

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
  measurements = [];
  kwh = 0;
  total_kwh = 0;

  constructor(private router: Router, private apiService: ApiService) {}

  async ngOnInit() {
    this.apiService.fetchMeasurements().then((result) => {
      console.log(result);
      this.measurements = result;
      this.kwh = this.convertTokwh();
      this.total_kwh = (this.kwh * this.tarifa);
    });
  }

  convertTokwh(intervaloSegundos = 2) {
    const energiaTotalKWh = this.measurements.reduce((total, medida:any) => {
      const energiaKWh = (medida.p_ativa * intervaloSegundos) / 3600000;
      return total + energiaKWh;
    }, 0);

    return Number(energiaTotalKWh.toFixed(6));
  }

  logout() {
    sessionStorage.clear();
    this.router.navigate(['']);
  }
}
