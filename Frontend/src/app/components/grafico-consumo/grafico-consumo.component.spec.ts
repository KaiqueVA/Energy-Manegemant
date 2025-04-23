import { ComponentFixture, TestBed } from '@angular/core/testing';

import { GraficoConsumoComponent } from './grafico-consumo.component';

describe('GraficoConsumoComponent', () => {
  let component: GraficoConsumoComponent;
  let fixture: ComponentFixture<GraficoConsumoComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [GraficoConsumoComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(GraficoConsumoComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
