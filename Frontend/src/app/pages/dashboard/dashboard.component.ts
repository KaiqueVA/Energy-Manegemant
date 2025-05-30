import { Component } from '@angular/core';
import { VisaoGeralComponent } from '../../components/visao-geral/visao-geral.component';
import { GraficoDonutComponent } from '../../components/grafico-donut/grafico-donut.component';
import { LineChartComponent } from '../../components/line-chart/line-chart.component';
import { HistoricoComponent } from '../../components/historico/historico.component';
import { SwitchTomadaComponent } from '../../components/switch-tomada/switch-tomada.component';
import { Router } from '@angular/router';
import { ApiService } from '../../services/api/api.service';

@Component({
  selector: 'app-dashboard',
  imports: [VisaoGeralComponent, GraficoDonutComponent, LineChartComponent, HistoricoComponent, SwitchTomadaComponent],
  templateUrl: './dashboard.component.html',
  styleUrl: './dashboard.component.scss'
})
export class DashboardComponent {
  username = sessionStorage.getItem('name');
  meuValor = false;

  constructor(private router: Router, private apiService: ApiService){

  }

  ngOnInit(){
    this.apiService.fetchMeasurements();
  }

  logout(){
    sessionStorage.clear();
    this.router.navigate(['']);
  }
}
